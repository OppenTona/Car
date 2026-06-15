#include <iostream>           // Thư viện nhập/xuất qua console
#include <GL/glut.h>           // Thư viện GLUT để quản lý cửa sổ và vẽ 3D
#include <GL/gl.h>             // Thư viện OpenGL để vẽ các đối tượng
#include <GL/glu.h>            // Thư viện GLU để thiết lập camera và phép chiếu
#include <cmath>               // Thư viện toán học để tính toán (như `PI`)

#define PI 3.14159265358979323846  // Định nghĩa hằng số PI

// Tọa độ ban đầu của xe
float carPosX = 0.0f, carPosY = 0.0f, carPosZ = 0.0f, carXoay = 0.0f;

// Thiết lập ánh sáng cho cảnh
void setupLighting() {
    glEnable(GL_LIGHTING);    // Kích hoạt hệ thống chiếu sáng của OpenGL
    glEnable(GL_LIGHT0);      // Bật nguồn sáng số 0 (mặc định)

    GLfloat lightPos[] = {10.0f, 10.0f, 10.0f, 1.0f};  // Vị trí nguồn sáng (x, y, z, w)
    GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};   // Màu sáng khuếch tán (diffuse) – trắng
    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f}; // Ánh sáng môi trường (ambient)

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);  // Thiết lập vị trí nguồn sáng
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor); // Thiết lập màu khuếch tán cho nguồn sáng
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); // Thiết lập ánh sáng môi trường
}


// Vẽ các trục tọa độ XYZ để dễ định hướng
void drawAxis() {
    glBegin(GL_LINES);            // Bắt đầu vẽ các đường thẳng
    glColor3f(1.0, 0.0, 0.0);     // Màu đỏ cho trục X
    glVertex3f(-15.0, 0.0, 0.0);  // Điểm đầu trục X
    glVertex3f(15.0, 0.0, 0.0);   // Điểm cuối trục X
    glEnd();                      // Kết thúc vẽ

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);     // Màu xanh lá cho trục Y
    glVertex3f(0.0, -15.0, 0.0);  // Điểm đầu trục Y
    glVertex3f(0.0, 15.0, 0.0);   // Điểm cuối trục Y
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);     // Màu xanh dương cho trục Z
    glVertex3f(0.0, 0.0, -15.0);  // Điểm đầu trục Z
    glVertex3f(0.0, 0.0, 15.0);   // Điểm cuối trục Z
    glEnd();
}

// Vẽ bánh xe ô tô
void drawWheel(float radius, float width) {
    glColor3f(0.1f, 0.1f, 0.1f);  // Đặt màu bánh xe là màu đen
    glPushMatrix();                // Lưu trạng thái hiện tại của ma trận
    glutSolidTorus(width / 2, radius, 20, 20);  // Vẽ bánh xe dưới dạng torus
    glPopMatrix();                 // Khôi phục ma trận ban đầu
}

// Vẽ thân xe
void drawCarBody() {
    glPushMatrix();                // Lưu trạng thái hiện tại của ma trận
    glColor3f(0.0f, 0.0f, 1.0f);  // Thân xe màu xanh dương
    glScalef(3.0f, 0.75f, 1.5f);  // Phóng to hình lập phương thành thân xe
    glutSolidCube(1.0);            // Vẽ hình lập phương
    glPopMatrix();                 // Khôi phục ma trận ban đầu

    // Vẽ mái xe
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.8f);  // Màu xanh dương đậm cho mái xe
    glTranslatef(0.0f, 0.5f, 0.0f); // Di chuyển mái xe lên trên thân xe
    glScalef(1.5f, 0.5f, 1.0f);   // Phóng to mái xe
    glutSolidCube(1.0);            // Vẽ mái xe dưới dạng hình lập phương
    glPopMatrix();
}

// Vẽ toàn bộ xe
void drawCar() {
    drawCarBody();  // Vẽ thân xe

    float wheelRadius = 0.3f;  // Bán kính bánh xe
    float wheelWidth = 0.2f;   // Chiều rộng bánh xe

    // Bánh trước-trái
    glPushMatrix();
    glTranslatef(1.5f, -0.5f, 0.8f); // Di chuyển bánh xe tới vị trí trước-trái
    drawWheel(wheelRadius, wheelWidth); // Vẽ bánh xe
    glPopMatrix();

    // Bánh trước-phải
    glPushMatrix();
    glTranslatef(1.5f, -0.5f, -0.8f); // Di chuyển bánh xe tới vị trí trước-phải
    drawWheel(wheelRadius, wheelWidth);
    glPopMatrix();

    // Bánh sau-trái
    glPushMatrix();
    glTranslatef(-1.5f, -0.5f, 0.8f); // Di chuyển bánh xe tới vị trí sau-trái
    drawWheel(wheelRadius, wheelWidth);
    glPopMatrix();

    // Bánh sau-phải
    glPushMatrix();
    glTranslatef(-1.5f, -0.5f, -0.8f); // Di chuyển bánh xe tới vị trí sau-phải
    drawWheel(wheelRadius, wheelWidth);
    glPopMatrix();
}

void drawSquare()
{
    glPushMatrix();
    glColor3f(0.0,0.0,1.0f);
    glScalef(10.0f,-0.1f,2.0f);
    glutSolidCube(3.0);
    glTranslatef(0.0,0.0,0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,10.0f,10.0f);
    glColor3f(0.0,0.0,1.0);
    glScalef(3.0f,10.0f,3.0f);
    glutSolidCube(3.0);
    glPopMatrix();
}

// Hàm hiển thị cảnh
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xóa màn hình và buffer độ sâu
    glLoadIdentity();  // Đặt ma trận hiện tại là ma trận đơn vị

    // Thiết lập camera (vị trí quan sát)
    gluLookAt(10+carPosX, 10+carPosY, carPosZ, carPosX, carPosY, carPosZ, 0, 1, 0);

    setupLighting();  // Kích hoạt ánh sáng
    drawAxis();       // Vẽ trục tọa độ


    drawSquare();

    glPushMatrix();  // Lưu trạng thái ma trận
    glTranslatef(carPosX, carPosY, carPosZ);  // Di chuyển xe tới tọa độ mới
    glRotatef(carXoay, 0, 0, 1);
    drawCar();  // Vẽ xe
    glPopMatrix();  // Khôi phục trạng thái ma trận ban đầu

    glFlush();  // Đẩy lệnh vẽ ra màn hình
}

// Hàm xử lý sự kiện khi thay đổi kích thước cửa sổ
void ReShape(int width, int height) {
    glViewport(0, 0, width, height);  // Đặt viewport theo kích thước mới
    glMatrixMode(GL_PROJECTION);  // Chuyển sang chế độ ma trận chiếu
    glLoadIdentity();  // Đặt ma trận đơn vị
    float ratio = (float)width / (float)height;  // Tính tỷ lệ khung hình
    gluPerspective(45.0, ratio, 1, 200.0);  // Thiết lập phép chiếu phối cảnh
    glMatrixMode(GL_MODELVIEW);  // Quay lại chế độ ma trận mô hình
}

// Khởi tạo OpenGL
void init() {
    glClearColor(0, 0, 0, 1);  // Đặt màu nền là đen
    glEnable(GL_DEPTH_TEST);   // Kích hoạt kiểm tra độ sâu
}

// Xử lý sự kiện bàn phím
void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': carPosX -= 0.5f; break;  // Di chuyển xe lên
        case 's': carPosX += 0.5f; break;  // Di chuyển xe xuống
        case 'a': carPosZ += 0.5f; break;  // Di chuyển xe sang trái
        case 'd': carPosZ -= 0.5f; break;  // Di chuyển xe sang phải
        case 'z': carPosY += 0.5f; break;  // Di chuyển xe ra trước
        case 'x': carPosY -= 0.5f; break;  // Di chuyển xe ra sau
        case 'q': carXoay += 10.0f; break;
        case 'e': carXoay -= 10.0f; break;
    }
    glutPostRedisplay();  // Cập nhật lại màn hình
}

// Hàm main
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Khởi tạo GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);  // Chế độ hiển thị RGB và độ sâu
    glutInitWindowSize(800, 600);  // Kích thước cửa sổ ban đầu
    glutCreateWindow("3D Car with OpenGL");  // Tạo cửa sổ với tiêu đề

    init();  // Khởi tạo các thiết lập ban đầu
    glutReshapeFunc(ReShape);  // Gán hàm xử lý khi thay đổi kích thước cửa sổ
    glutDisplayFunc(MyDisplay);  // Gán hàm hiển thị
    glutKeyboardFunc(handleKeyboard);  // Gán hàm xử lý bàn phím
    glutMainLoop();  // Bắt đầu vòng lặp sự kiện

    return 0;  // Kết thúc chương trình
}