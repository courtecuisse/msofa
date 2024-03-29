#include <gui/Simulation.h>
#include <iostream>
#include <fstream>
#include <animationloop/DefaultAnimationLoop.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <QFile>

Simulation::Simulation() {
    light_ambient = TColor(0.2f, 0.2f, 0.2f, 1.0f);
    light0_color = TColor(0.75f, 0.75f, 0.9f, 1.0f);
    light1_color = TColor(0.4f, 0.4f ,0.4f ,1.0f);

    m_time = 0;
    main_Node = NULL;
}

double Simulation::getPickingStiffness() {
    return pickingForceField.d_stiffness.getValue();
}

void Simulation::addPickingStiffness(double a) {
    pickingForceField.d_stiffness.setValue(pickingForceField.d_stiffness.getValue() + a);
}

bool Simulation::read_scene(const char * fn) {
    m_filename = getFullPath(fn);

    QFile fileScn(m_filename.c_str());

    if (!fileScn.open(QIODevice::ReadOnly)) return false;

    main_Node = new Node();

    QXmlStreamReader xml(&fileScn);
    xml.readNextStartElement();
    processNode(main_Node,xml);

    return true;
}

std::string Simulation::getFileName() {
    return m_filename;
}

void Simulation::processNode(Node * node,QXmlStreamReader & xml) {
    if (xml.name() != "Node") return;

    QXmlStreamAttributes attributes = xml.attributes();
    for (int i=0;i<attributes.size();i++) {
        node->setAttribute(attributes[i].name().toString().toStdString().c_str(),
                           attributes[i].value().toString().toStdString().c_str());

    }

    while (! xml.atEnd()) {
        xml.readNextStartElement();

        if (xml.tokenType() == QXmlStreamReader::TokenType::StartElement) {
            std::string className = xml.name().toString().toStdString();

            BaseObject * obj = Factory::getInstance(className.c_str());

            if (obj != NULL) {
                node->attach(obj);

                QXmlStreamAttributes attributes = xml.attributes();
                for (int i=0;i<attributes.size();i++) {
                    obj->setAttribute(attributes[i].name().toString().toStdString().c_str(),
                                      attributes[i].value().toString().toStdString().c_str());

                }

                if (Node* newctx = dynamic_cast<Node*>(obj)) processNode(newctx,xml);
            } else {
                std::cerr << "Error cannot create " << className << std::endl;
            }
        } else if (xml.tokenType() == QXmlStreamReader::TokenType::EndElement) {
            if (xml.name() == "Node") return;
        }
    }
}

void Simulation::init()
{
    main_Node->init();

    m_bbox = ComputeBBoxVisitor().get(main_Node);

    TReal simulation_size = (m_bbox.max-m_bbox.min).norm();
    TVec3 simulation_center = (m_bbox.min + m_bbox.max) * 0.5f;

    light0_position = simulation_center + TVec3(0.0f,2.0f,0.0f)*simulation_size;
    light1_position = simulation_center + TVec3(3.0f,-0.5f,-1.0f)*simulation_size;
    reset_camera();

//    pGLUquadric = gluNewQuadric();

    glDepthFunc(GL_LEQUAL);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);


    GLfloat    vzero[4] = {0, 0, 0, 0};
    GLfloat    vone[4] = {1, 1, 1, 1};

    GLfloat    light_ambient_ptr[4] = {(GLfloat) light_ambient[0],(GLfloat)  light_ambient[1],(GLfloat)  light_ambient[2],(GLfloat) light_ambient[3]};
    GLfloat    light0_color_ptr[4] = {(GLfloat) light0_color[0],(GLfloat)  light0_color[1],(GLfloat)  light0_color[2],(GLfloat) light0_color[3]};
    GLfloat    light0_position_ptr[4] = {(GLfloat) light0_position[0],(GLfloat)  light0_position[1],(GLfloat)  light0_position[2],(GLfloat) 1.0};

    GLfloat    light1_color_ptr[4] = {(GLfloat) light1_color[0],(GLfloat)  light1_color[1],(GLfloat)  light1_color[2],(GLfloat) light1_color[3]};
    GLfloat    light1_position_ptr[4] = {(GLfloat) light1_position[0],(GLfloat)  light1_position[1],(GLfloat)  light1_position[2],(GLfloat) 1.0};

    // Set light model
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_ptr);

    // Setup 'light 0'
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, vzero);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_color_ptr);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_color_ptr);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position_ptr);

    // Setup 'light 1'
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, vzero);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_color_ptr);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_color_ptr);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position_ptr);

    // Enable color tracking
    glMaterialfv(GL_FRONT, GL_AMBIENT, vone);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, vone);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    // disable specular
    //glMaterialfv(GL_FRONT, GL_SPECULAR, vzero);
    glMaterialfv(GL_FRONT, GL_SPECULAR, vone);
    glMateriali(GL_FRONT, GL_SHININESS, 100);

    glEnableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_NORMAL_ARRAY);
}

template<class T>
class FindVisitor : public Visitor {
public:

    FindVisitor() {
        m_object = NULL;
    }

    bool processObject(BaseObject * o)  {
        if (dynamic_cast<T *>(o)) {
            m_object = (T *) o;
            return false;
        }

        return true;
    }

    T * getObject() {
        return m_object;
    }

    static T * find(Context * c) {
        FindVisitor<T> visitor;
        visitor.execute(c);
        return visitor.getObject();
    }

public:
    T * m_object;
};

void Simulation::step() {
    updatePickingForce();

    AnimationLoop * anim = FindVisitor<AnimationLoop>::find(main_Node);
    if (anim == NULL) {
        anim = new DefaultAnimationLoop();
        main_Node->attach(anim);
    }

    m_time += main_Node->getDt();
    anim->step(m_time);
}

double Simulation::getSize() {
    return (m_bbox.max-m_bbox.min).norm();
}

//// MAIN METHOD ////

void Simulation::render(DisplayFlag displayFlag)
{
    camera_position = camera_lookat + camera_direction * camera_distance;
    glMatrixMode   ( GL_MODELVIEW );  // Select The Model View Matrix
    glLoadIdentity ( );               // Reset The Model View Matrix
    gluLookAt(camera_position[0], camera_position[1], camera_position[2],
              camera_lookat[0], camera_lookat[1], camera_lookat[2],
              0, 1, 0);

    GLfloat    light0_position_ptr[4] = {(GLfloat) light0_position[0],(GLfloat)  light0_position[1],(GLfloat)  light0_position[2],(GLfloat) 1.0};
    GLfloat    light1_position_ptr[4] = {(GLfloat) light1_position[0],(GLfloat)  light1_position[1],(GLfloat)  light1_position[2],(GLfloat) 1.0};


    glLightfv(GL_LIGHT0, GL_POSITION, light0_position_ptr);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position_ptr);

    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    main_Node->draw(displayFlag);
}

void Simulation::reset_camera()
{
    TReal simulation_size = (m_bbox.max-m_bbox.min).norm();
    TVec3 simulation_center = (m_bbox.min + m_bbox.max) * 0.5f;

    camera_lookat = simulation_center;
    camera_lookat[2] += simulation_size*0.1f;
    camera_distance = simulation_size*1.2f;
    camera_direction = TVec3(1.0f,0.25f,1.0f);
    camera_direction.normalize();
    camera_position = simulation_center + camera_direction * camera_distance;
}

void Simulation::rotateCamera(int dx,int dy) {
    TVec3 vx = camera_direction.cross(TVec3(0,1,0));
    TVec3 vy = vx.cross(camera_direction);
    vx.normalize();
    vy.normalize();
    camera_direction += (vx*dx + vy*dy)*0.005;
    camera_direction.normalize();
}

void Simulation::translateCamera(int dx,int dy) {
    TVec3 vx = camera_direction.cross(TVec3(0,1,0));
    TVec3 vy = vx.cross(camera_direction);
    vx.normalize();
    vy.normalize();

    camera_lookat += (vx*dx + vy*dy)*(camera_distance*0.001);
}

void Simulation::zoomCamera(int dx,int dy) {
    TVec3 vx = camera_direction.cross(TVec3(0,1,0));
    TVec3 vy = vx.cross(camera_direction);
    vx.normalize();
    vy.normalize();

    camera_distance *= pow(0.99,dy);
}

void Simulation::updatePickingForce() {
    if (pickingForceField.getContext() == NULL) return;

    const std::vector<TVec3> & pos = pickingForceField.getContext()->getMstate()->get(VecID::position);
    if (pickingForceField.d_index.getValue() == -1) return;

    TVec3 particle = pos[pickingForceField.d_index.getValue()];
    pickingForceField.d_force.setValue(picked_origin + picked_dir * (particle-picked_origin).dot(picked_dir) - particle);
}

void Simulation::updatePickingForce(int x,int y) {
    update_picking_org(x,y);
    updatePickingForce();
}

void Simulation::updatePickingConstraint(int x,int y) {
    update_picking_org(x,y);
    if (pickingConstraint.getContext() == NULL) return;
    if (pickingConstraint.d_index.getValue() == -1) return;

    const std::vector<TVec3> & pos = pickingConstraint.getContext()->getMstate()->get(VecID::position);
    TVec3 particle = pos[pickingConstraint.d_index.getValue()];
    pickingConstraint.d_position.setValue(picked_origin + picked_dir * (particle-picked_origin).dot(picked_dir));
}

void Simulation::startForcePicking(int x,int y) {
    update_picking_org(x,y);

    PickingVisitor v(picked_origin,picked_dir,true);
    main_Node->processVisitor(v);
    if (v.getPickedState() == NULL) return;

    Node * node = dynamic_cast<Node *>(v.getPickedState()->getContext());
    node->attach(&pickingForceField);
    pickingForceField.d_index.setValue(v.getIndice());
    pickingForceField.d_force.setValue(TVec3());
}

void Simulation::stopForcePicking() {
    if (pickingForceField.getContext() == NULL) return;
    pickingForceField.d_index.setValue(-1);
    Node * node = dynamic_cast<Node *>(pickingForceField.getContext());
    node->detach(&pickingForceField);
}

void Simulation::startConstraintPicking(int x,int y) {
    update_picking_org(x,y);

    PickingVisitor v(picked_origin,picked_dir,false);
    main_Node->processVisitor(v);
    if (v.getPickedState() == NULL) {
        if (pickingConstraint.getContext() == NULL) return;
        pickingConstraint.d_index.setValue(-1);
        Node * node = dynamic_cast<Node *>(pickingConstraint.getContext());
        node->detach(&pickingConstraint);

        return;
    }

    const std::vector<TVec3> & pos = v.getPickedState()->get(VecID::position);

    Node * node = dynamic_cast<Node *>(v.getPickedState()->getContext());
    node->attach(&pickingConstraint);
    pickingConstraint.d_index.setValue(v.getIndice());
    pickingConstraint.d_position.setValue(pos[v.getIndice()]);
}

void Simulation::stopConstraintPicking() {

}

void Simulation::update_picking_org(int x, int y) {
    double viewmatrix[16];
    glGetDoublev(GL_MODELVIEW_MATRIX,viewmatrix);
    double projmatrix[16];
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    double obj_x = 0, obj_y = 0, obj_z = 0;
    gluUnProject(x, viewport[3]-y, 0, viewmatrix, projmatrix, viewport, &obj_x, &obj_y, &obj_z);

    picked_origin = camera_position;

//    std::cout << " x " << x << " " << y << " " << viewport[2] << " " << viewport[3] << std::endl;
//    std::cout << picked_origin << std::endl;
    picked_dir = TVec3(obj_x, obj_y, obj_z) - picked_origin;

//    std::cout << picked_dir << std::endl;
    picked_dir.normalize();
}


