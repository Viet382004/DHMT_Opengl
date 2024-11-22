#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Vector_Matrix.h>


using namespace std;

typedef struct
{
	float xyzw[4];
	//float rgba[4];
	float normal[4];
} Vertex;
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
	// Mảng dữ liệu
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },/*{ 1.0f, 1.0f, 0.0f, 1.0f },*/{ 0, 0, 1, 0 } },
	{ { -0.5f,	 0.5f,	0.5f, 1.0 },/*{ 1.0f, 1.0f, 0.0f, 1.0f },*/{ 0, 0, 1, 0 } },
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },/*{ 1.0f, 1.0f, 0.0f, 1.0f },*/{ 0, 0, 1, 0 } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1, 0, 0, 0 } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1, 0, 0, 0 } },

	// v0-v5-v6 (top)
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	// v6-v1-v0
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	// v3-v2-v7
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },

	// v4-v7-v6 (back)
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } }
};
// ----------------------------------------

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].xyzw);
const size_t NormalOffset = sizeof(Vertices[0].xyzw) /*+ sizeof(Vertices[1].rgba)*/;

int CurrentWidth = 800,
CurrentHeight = 800;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4
model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;

int
model_mat_location,
view_mat_location,
projection_mat_location;

float
r[] = { 0.0f, 0.0f, 0.0f },
s[] = { 1.0f, 1.0f, 1.0f },
t[] = { 0.0f, 0.0f, 0.0f };


bool
translated = false,
rotated = false,
scaled = false;
// ------------------------------------------
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);	// position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset); //color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset); //normal

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}
// ------------------------------------------
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ------------------------------------------
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}




//======================================================
//=========================ĐÔNG=========================
//======================================================
//================================PHÒNG CHÍNH=====================================
mat4 model_phongchinh;

void TuongBen(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_phongchinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0, 0.72, 0.25);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SanNha(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_phongchinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.75, 0.6, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TranNha(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_phongchinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0, 0.93, 0.87);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TuongSau(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_phongchinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0, 0.72, 0.25);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TuongTruoc(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_phongchinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0, 0.72, 0.25);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void phongchinh(float x, float y, float z, int goc)
{
	model_phongchinh = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.0, 1.0, 1.0));

	TuongBen(10.0, 0.0, 0.0, 0.2, 14.0, 50.0);//phải
	//TuongBen(-10.0, 0.0, 0.0, 0.2, 14.0, 50.0);//trai
	TuongBen(-10.0, 0.0, 2.25, 0.2, 14.0, 4.5);//trai
	TuongBen(-10.0, 0.0, 10.75, 0.2, 14.0, 4.5);//trai
	TuongBen(-10.0, 0.0, -14.5, 0.2, 14.0, 21);//trai
	TuongBen(-10.0, 0.0, 21, 0.2, 14.0, 8);//trai
	TuongBen(-10.0, 4.4, -2, 0.2, 5.25, 4);//trai
	TuongBen(-10.0, -4.65, -2, 0.2, 4.8, 4);//trai
	TuongBen(-10.0, 4.4, 6.5, 0.2, 5.25, 4);//trai
	TuongBen(-10.0, -4.65, 6.5, 0.2, 4.8, 4);//trai
	TuongBen(-10.0, 4.4, 15, 0.2, 5.25, 4);//trai
	TuongBen(-10.0, -4.65, 15, 0.2, 4.8, 4);//trai

	TuongTruoc(-7.75, 4.5, 25.1, 4.5, 5, 0.2);
	TuongTruoc(2.3, -5, 25.1, 15.5, 4, 0.2);
	TuongTruoc(-4, 0, 25.1, 3, 14, 0.2);


	TuongSau(0, 0, -25.1, 20, 14.2, 0.2);
	SanNha(0, -7.1, 0, 28.2, 0.2, 60.0);
	TranNha(0, 7.1, 0, 20.2, 0.2, 50.0);
}


//===============================QUẠT TRẦN==================================
mat4 model_quattran;
float qtqt[] = { 0, 0, 0 };
//bool check_qt = false;
int tocdo_qt = 0;

void captreo_quattran(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {

		instance = translate(vec3(x, y, z)) * rotate_y(i)* scale(vec3(0.5, 0.5, 0.1));
		mat4 model_base = model_quattran * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.96, 0.57, 0.55);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void thanhtreo_quattran(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {

		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(0.1, 1.0, 0.1));
		mat4 model_base = model_quattran * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.5, 0.5);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void nap_quattran(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {

		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(0.4, 0.2, 0.1));
		mat4 model_base = model_quattran * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.75, 0.81, 0.83);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void dongco_quattran(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {

		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(1.0, 0.2, 0.1));
		mat4 model_base = model_quattran * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.96, 0.57, 0.55);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void canhquat_quattran(float x, float y, float z, int goc)
{
	mat4 instance = identity_mat4();
	instance = rotate_y(goc) * translate(vec3(x, y, z)) * scale(vec3(2.5, 0.05, 0.5));
	mat4 model_base = model_quattran * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.5, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void quattran(float x, float y, float z, int goc)
{
	model_quattran = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.0, 1.0, 1.0));

	captreo_quattran(0, 0, 0);
	thanhtreo_quattran(0.0, -0.75, 0.0);
	nap_quattran(0.0, -1.35, 0.0);

	mat4 model_quattran_bd = model_quattran;
	// Chỉnh tốc độ quay của quạt(max: 3 -> 1:min)
	switch (tocdo_qt)
	{
	case 0:
		model_quattran = model_quattran_bd;
		break;
	case 1:
		model_quattran = model_quattran_bd * rotate_y(qtqt[0]);
		break;
	case 2:
		model_quattran = model_quattran_bd * rotate_y(qtqt[1]);
		break;
	case 3:
		model_quattran = model_quattran_bd * rotate_y(qtqt[2]);
		break;
	default:
		break;
	}

	dongco_quattran(0.0, -1.55, 0.0);
	canhquat_quattran(1.25, -1.55, -0.0, 0);	// Cánh quạt 1
	canhquat_quattran(1.25, -1.55, -0.0, 120);	// Cánh quạt 2
	canhquat_quattran(1.25, -1.55, -0.0, 240);	// Cánh quạt 3
}

void nhieu_quattran()
{
	quattran(4.0, 6.75, 10.0, 0);
	quattran(4.0, 6.75, 3.0, 0);
	quattran(4.0, 6.75, -4.0, 0);
	quattran(-4.0, 6.75, 10.0, 0);
	quattran(-4.0, 6.75, 3.0, 0);
	quattran(-4.0, 6.75, -4.0, 0);
}

//===============================QUẠT CÂY==================================
mat4 model_quatcay, model_view_quatcay;
float qcqc[] = { 0, 0, 0 , 0, 0 };
int tupnang = 0;
float tocdo_qc_tupnang = 0.5f;
int tocdo_qc_canh = 0;

void de_quatcay(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {
		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(2.0, 0.2, 0.1));
		mat4 model_base = model_quatcay * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.96, 0.57, 0.55);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void than_quatcay(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.4, 2.4, 0.4));
	mat4 model_base = model_quatcay * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.5, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void docao_quatcay(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {
		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(0.2, 1.4, 0.1));
		mat4 model_base = model_quatcay * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.76, 0.81, 0.84);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void dongco_quatcay(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.6, 0.6, 1.0));
	mat4 model_base = model_quatcay * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.5, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void truc_quatcay(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {
		instance = translate(vec3(x, y, z)) * rotate_z(i) * scale(vec3(0.2, 0.2, 0.4));
		mat4 model_base = model_quatcay * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.76, 0.81, 0.84);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void trunoicanhquat_quatcay(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {
		instance = translate(vec3(x, y, z)) * rotate_z(i) * scale(vec3(0.4, 0.4, 0.2));
		mat4 model_base = model_quatcay * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.96, 0.57, 0.55);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void canhquat_quatcay(float x, float y, float z, int goc)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, y - 0.7, 0)) * rotate_z(goc) * translate(vec3(0, -y + 0.7, 0)) * translate(vec3(x, y, z)) * scale(vec3(0.3, 1.4, 0.05));
	mat4 model_base = model_quatcay * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.5, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void quatcay(float x, float y, float z, int goc)
{
	model_quatcay = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.0, 1.0, 1.0));

	model_quatcay = model_quatcay * translate(vec3(qcqc[4], 0, 0));
	de_quatcay(0, 0, 0);
	than_quatcay(0.0, 1.3, 0.0);

	model_quatcay = model_quatcay * translate(vec3(0.0, qcqc[0], 0.0));
	docao_quatcay(0.0, 3.2, 0.0);

	switch (tupnang)
	{
	case 0:
		model_quatcay = model_quatcay * translate(vec3(0.0, 0.0, -0.2)) * rotate_y(qcqc[1]) * translate(vec3(0.0, 0.0, 0.2));
		break;
	case 1:
		model_quatcay = model_quatcay * translate(vec3(0.0, 0.0, -0.2)) * rotate_y(qcqc[1]) * translate(vec3(0.0, 0.0, 0.2));
		break;
	default:
		break;
	}
	dongco_quatcay(0.0, 4.0, -0.2);

	//========================

	mat4 model_quatcay_bandau = model_quatcay;
	switch (tocdo_qc_canh)
	{
	case 0:
		model_quatcay = model_quatcay;
		break;
	case 1:
		model_quatcay = model_quatcay_bandau * translate(vec3(0.0, 4.0, 0.0)) * rotate_z(qcqc[2]) * translate(vec3(0.0, -4.0, 0.0));
		break;
	case 2:
		model_quatcay = model_quatcay_bandau * translate(vec3(0.0, 4.0, 0.0)) * rotate_z(qcqc[3]) * translate(vec3(0.0, -4.0, 0.0));
		break;
	default:
		break;
	}
	truc_quatcay(0.0, 4.0, -0.9);
	trunoicanhquat_quatcay(0.0, 4.0, -1.2);
	canhquat_quatcay(0.0, 4.7, -1.2, 0);
	canhquat_quatcay(0.0, 4.7, -1.2, 120);
	canhquat_quatcay(0.0, 4.7, -1.2, 240);
}

void nhieu_quatcay()
{
	quatcay(8.5,	-6.9, 2.8, 90);
	quatcay(8.5,	-6.9, -4.2, 90);
	quatcay(8.5,	-6.9, 9.8, 90);
	quatcay(-8.5,	-6.9, 2.8, -90);
	quatcay(-8.5,	-6.9, -4.2, -90);
	quatcay(-8.5,	-6.9, 9.8, -90);

}



//========================TỦ TRƯNG BÀY NƯỚC NGỌT=============================
mat4 model_tunuocngot, model_view_tunuocngot;
float nuocngot[] = { 0,0,0 };

void day_tunuocngot(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(3.0, 1.0, 2.0));
	mat4 model_base = model_tunuocngot * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.3, 0.73, 0.47);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanhben_tunuocngot(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.2, 4.0, 2.0));
	mat4 model_base = model_tunuocngot * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.03, 0.58, 0.21);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanhsau_tunuocngot(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2.6, 4.0, 0.2));
	mat4 model_base = model_tunuocngot * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.03, 0.58, 0.21);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ngan_tunuocngot(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2.6, 0.1, 1.6));
	mat4 model_base = model_tunuocngot * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.84, 0.33);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanhtren_tunuocngot(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(3.0, 0.4, 2.0));
	mat4 model_base = model_tunuocngot * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.3, 0.73, 0.47);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void lothongkhi_tunuocngot(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2.4, 0.02, 0.05));
	mat4 model_base = model_tunuocngot * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0, 1.0, 1.0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chan_tunuocngot(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.4, 0.4, 0.4));
	mat4 model_base = model_tunuocngot * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.03, 0.58, 0.21);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//===================================LON NƯỚC NGỌT=====================================

void lonnuoc_tunuocngot(float x, float y, float z, float r, float g, float b)
{
	mat4 instance = identity_mat4();
	for (float i = 0; i <= 360; i += 1.0) {
		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(0.3, 0.6, 0.1));
		mat4 model_base = model_tunuocngot * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void naplonnuoc_tunuocngot(float x, float y, float z, float r, float g, float b)
{
	mat4 instance = identity_mat4();
	for (float i = 0; i <= 360; i += 1.0) {
		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(0.3, 0.05, 0.1));
		mat4 model_base = model_tunuocngot * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void lonnuoc_do_tunuocngot(float x, float y, float z)
{
	lonnuoc_tunuocngot(x, y, z, 1.0, 0.2, 0.2);
	naplonnuoc_tunuocngot(x, y + 0.325, z, 1.0, 0.76, 0);
}

void lonnuoc_xanh_tunuocngot(float x, float y, float z)
{
	lonnuoc_tunuocngot(x, y, z, 0.06, 0.06, 0.59);
	naplonnuoc_tunuocngot(x, y + 0.325, z, 1.0, 0.08, 0);
}

void lonnuoc_cam_tunuocngot(float x, float y, float z)
{
	lonnuoc_tunuocngot(x, y, z, 0.94, 0.53, 0.04);
	naplonnuoc_tunuocngot(x, y + 0.325, z, 0.39, 0.56, 0.16);
}

void lonnuoc_xanh2_tunuocngot(float x, float y, float z)
{
	lonnuoc_tunuocngot(x, y, z, 0.59, 0.73, 0.8);
	naplonnuoc_tunuocngot(x, y + 0.325, z, 1, 1, 1);
}

void lonnuoc_xanh3_tunuocngot(float x, float y, float z)
{
	lonnuoc_tunuocngot(x, y, z, 0.2, 0.71, 0.4);
	naplonnuoc_tunuocngot(x, y + 0.325, z, 0.96, 0.83, 0.09);
}

void lonnuoctang1_tunuocngot()
{
	// Hàng 1 (trong cùng):
	lonnuoc_xanh_tunuocngot(1.0, -1.2, -3.5);
	lonnuoc_cam_tunuocngot(0.5, -1.2, -3.5);
	lonnuoc_do_tunuocngot(0.0, -1.2, -3.5);
	lonnuoc_xanh2_tunuocngot(-0.5, -1.2, -3.5);
	lonnuoc_xanh3_tunuocngot(-1.0, -1.2, -3.5);

	// Hàng 2 (ở giữa):
	lonnuoc_xanh_tunuocngot(1.0, -1.2, -4.0);
	lonnuoc_cam_tunuocngot(0.5, -1.2, -4.0);
	lonnuoc_do_tunuocngot(0.0, -1.2, -4.0);
	lonnuoc_xanh2_tunuocngot(-0.5, -1.2, -4.0);
	lonnuoc_xanh3_tunuocngot(-1.0, -1.2, -4.0);

	// Hàng 3 (bên ngoài):
	lonnuoc_xanh_tunuocngot(1.0, -1.2, -4.5);
	lonnuoc_cam_tunuocngot(0.5, -1.2, -4.5);
	lonnuoc_do_tunuocngot(0.0, -1.2, -4.5);
	lonnuoc_xanh2_tunuocngot(-0.5, -1.2, -4.5);
	lonnuoc_xanh3_tunuocngot(-1.0, -1.2, -4.5);
}

void lonnuoctang2_tunuocngot()
{
	// Hàng 1 (trong cùng):
	lonnuoc_xanh_tunuocngot(1.0, -0.15, -3.5);
	lonnuoc_cam_tunuocngot(0.5, -0.15, -3.5);
	lonnuoc_do_tunuocngot(0.0, -0.15, -3.5);
	lonnuoc_xanh2_tunuocngot(-0.5, -0.15, -3.5);
	lonnuoc_xanh3_tunuocngot(-1.0, -0.15, -3.5);

	// Hàng 2 (ở giữa):
	lonnuoc_xanh_tunuocngot(1.0, -0.15, -4.0);
	lonnuoc_cam_tunuocngot(0.5, -0.15, -4.0);
	lonnuoc_do_tunuocngot(0.0, -0.15, -4.0);
	lonnuoc_xanh2_tunuocngot(-0.5, -0.15, -4.0);
	lonnuoc_xanh3_tunuocngot(-1.0, -0.15, -4.0);

	// Hàng 3 (bên ngoài):
	lonnuoc_xanh_tunuocngot(1.0, -0.15, -4.5);
	lonnuoc_cam_tunuocngot(0.5, -0.15, -4.5);
	lonnuoc_do_tunuocngot(0.0, -0.15, -4.5);
	lonnuoc_xanh2_tunuocngot(-0.5, -0.15, -4.5);
	lonnuoc_xanh3_tunuocngot(-1.0, -0.15, -4.5);
}

void lonnuoctang3_tunuocngot()
{
	// Hàng 1 (trong cùng):
	lonnuoc_xanh_tunuocngot(1.0, 0.85, -3.5);
	lonnuoc_cam_tunuocngot(0.5, 0.85, -3.5);
	lonnuoc_do_tunuocngot(0.0, 0.85, -3.5);
	lonnuoc_xanh2_tunuocngot(-0.5, 0.85, -3.5);
	lonnuoc_xanh3_tunuocngot(-1.0, 0.85, -3.5);

	// Hàng 2 (ở giữa):
	lonnuoc_xanh_tunuocngot(1.0, 0.85, -4.0);
	lonnuoc_cam_tunuocngot(0.5, 0.85, -4.0);
	lonnuoc_do_tunuocngot(0.0, 0.85, -4.0);
	lonnuoc_xanh2_tunuocngot(-0.5, 0.85, -4.0);
	lonnuoc_xanh3_tunuocngot(-1.0, 0.85, -4.0);

	// Hàng 3 (bên ngoài):
	lonnuoc_xanh_tunuocngot(1.0, 0.85, -4.5);
	lonnuoc_cam_tunuocngot(0.5, 0.85, -4.5);
	lonnuoc_do_tunuocngot(0.0, 0.85, -4.5);
	lonnuoc_xanh2_tunuocngot(-0.5, 0.85, -4.5);
	lonnuoc_xanh3_tunuocngot(-1.0, 0.85, -4.5);
}

void lonnuoctang4_tunuocngot()
{
	// Hàng 1 (trong cùng):
	lonnuoc_xanh_tunuocngot(1.0, 1.85, -3.5);
	lonnuoc_cam_tunuocngot(0.5, 1.85, -3.5);
	lonnuoc_do_tunuocngot(0.0, 1.85, -3.5);
	lonnuoc_xanh2_tunuocngot(-0.5, 1.85, -3.5);
	lonnuoc_xanh3_tunuocngot(-1.0, 1.85, -3.5);

	// Hàng 2 (ở giữa):
	lonnuoc_xanh_tunuocngot(1.0, 1.85, -4.0);
	lonnuoc_cam_tunuocngot(0.5, 1.85, -4.0);
	lonnuoc_do_tunuocngot(0.0, 1.85, -4.0);
	lonnuoc_xanh2_tunuocngot(-0.5, 1.85, -4.0);
	lonnuoc_xanh3_tunuocngot(-1.0, 1.85, -4.0);

	// Hàng 3 (bên ngoài):
	lonnuoc_xanh_tunuocngot(1.0, 1.85, -4.5);
	lonnuoc_cam_tunuocngot(0.5, 1.85, -4.5);
	lonnuoc_do_tunuocngot(0.0, 1.85, -4.5);
	lonnuoc_xanh2_tunuocngot(-0.5, 1.85, -4.5);
	lonnuoc_xanh3_tunuocngot(-1.0, 1.85, -4.5);
}


//========================KHUNG CỬA TỦ TRƯNG BÀY NƯỚC NGỌT=============================

void khungcua_tunuocngot(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_tunuocngot * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.94, 0.53, 0.04);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void kinh_tunuocngot(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2.4, 3.8, 0.1));
	mat4 model_base = model_tunuocngot * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.75, 1);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void taynam_tunuocngot(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_tunuocngot * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.94, 0.53, 0.04);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void tunuocngot(float x, float y, float z, int goc)
{
	model_tunuocngot = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.4, 1.4, 1.4));;
	day_tunuocngot(0.0, -2.0, -4.0);
	thanhben_tunuocngot(1.4, 0.5, -4.0); // thanh tu ben trai
	thanhben_tunuocngot(-1.4, 0.5, -4.0); // thanh tu ben phai

	thanhsau_tunuocngot(0.0, 0.5, -3.1);

	ngan_tunuocngot(0.0, -0.5, -4.0);
	ngan_tunuocngot(0.0, 0.5, -4.0);
	ngan_tunuocngot(0.0, 1.5, -4.0);

	thanhtren_tunuocngot(0.0, 2.7, -4.0);

	lothongkhi_tunuocngot(0.0, -1.8, -5.0);
	lothongkhi_tunuocngot(0.0, -2.0, -5.0);
	lothongkhi_tunuocngot(0.0, -2.2, -5.0);

	chan_tunuocngot(1.1, -2.7, -4.7);	// chan 1
	chan_tunuocngot(-1.1, -2.7, -4.7);	// chan 2
	chan_tunuocngot(1.1, -2.7, -3.3);	// chan 3
	chan_tunuocngot(-1.1, -2.7, -3.3);	// chan 4

	//=====================LON NƯỚC NGỌT=====================
	lonnuoctang1_tunuocngot();
	lonnuoctang2_tunuocngot();
	lonnuoctang3_tunuocngot();
	lonnuoctang4_tunuocngot();

	//=================KHUNG TỦ TRƯNG BÀY NƯỚC NGỌT=============
	model_tunuocngot = model_tunuocngot * translate(vec3(1.2, 0, -4.95)) * rotate_y(nuocngot[0]) * translate(vec3(-1.2, 0, 4.95));
	khungcua_tunuocngot(0.0, -1.45, -4.95, 2.6, 0.1, 0.1); // khung cửa dưới
	khungcua_tunuocngot(0.0, 2.45, -4.95, 2.6, 0.1, 0.1); // khung cửa trên
	khungcua_tunuocngot(1.25, 0.5, -4.95, 0.1, 3.8, 0.1); // khung cửa trai
	khungcua_tunuocngot(-1.25, 0.5, -4.95, 0.1, 3.8, 0.1); // khung cửa phai
	
	kinh_tunuocngot(0.0, 0.5, -4.95);
	
	taynam_tunuocngot(-0.9, 0.25, -5.125, 0.1, 0.1, 0.25);
	taynam_tunuocngot(-0.9, 0.5, -5.2, 0.1, 0.5, 0.1);
	taynam_tunuocngot(-0.9, 0.75, -5.125, 0.1, 0.1, 0.25);
}



//===================================CỬA WC================================
mat4 model_cuawc, model_view_cuawc;
float cwc[] = { 0, 0, 0 };

void khung_cuawc(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_cuawc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.86, 0.67, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thonggio_cuawc(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2.2, 1.4, 0.1));
	mat4 model_base = model_cuawc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.82, 0.53, 0.3);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void lo_thonggio_cuawc(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * rotate_x(-45) * scale(vec3(1.8, 0.05, 0.15));
	mat4 model_base = model_cuawc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.86, 0.67, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void kinh_cuawc(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2.2, 2.2, 0.1));
	mat4 model_base = model_cuawc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.75, 1);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void khoa_cuawc(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_cuawc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.5, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void cua_wc(float x, float y, float z, int goc)
{
	model_cuawc = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.2, 1.2, 1.2));
	model_cuawc = model_cuawc * translate(vec3(1.5, 0.0, 0.0)) * rotate_y(cwc[1]) * translate(vec3(-1.5, 0.0, 0.0));

	khung_cuawc(0.0, -3.0, 0.0, 3.0, 0.4, 0.1);		//khung dưới cửa wc
	khung_cuawc(1.3, -0.2, 0.0, 0.4, 5.2, 0.1);		//khung trai cửa wc
	khung_cuawc(-1.3, -0.2, 0.0, 0.4, 5.2, 0.1);	//khung phai cửa wc
	khung_cuawc(0.0, -0.8, 0.0, 2.2, 1.2, 0.1);		//khung giua cửa wc
	khung_cuawc(0.0, 2.2, 0.0, 2.2, 0.4, 0.1);		//khung tren cửa wc
	
	thonggio_cuawc(0.0, -2.1, 0.0);
	lo_thonggio_cuawc(0.0, -1.6, -0.1);
	lo_thonggio_cuawc(0.0, -1.9, -0.1);
	lo_thonggio_cuawc(0.0, -2.2, -0.1);
	lo_thonggio_cuawc(0.0, -2.5, -0.1);
	kinh_cuawc(0.0, 0.9, 0.0);

	model_cuawc = model_cuawc * translate(vec3(-1.25, -0.5, 0.0)) * rotate_z(-cwc[1]) * translate(vec3(1.25, 0.5, 0.0));
	khoa_cuawc(-1.4, -0.5, 0.0, 0.4, 0.06, 0.06);			// khóa (chốt cửa)
	khoa_cuawc(-1.25, -0.5, -0.14, 0.1, 0.1, 0.22);		// khóa bên ngoài
	khoa_cuawc(-1.0, -0.5, -0.3, 0.6, 0.1, 0.1);			// khóa bên ngoài
	khoa_cuawc(-1.25, -0.5, 0.14, 0.1, 0.1, 0.22);		// khóa bên trong
	khoa_cuawc(-1.0, -0.5, 0.3, 0.6, 0.1, 0.1);			// khóa bên trong
}



//======================================TƯỜNG WC=================================
mat4 model_tuongwc, model_view_tuongwc;

void tuongsau_wc(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(8.0, 8.0, 0.2));
	mat4 model_base = model_tuongwc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.87, 0.83, 0.77);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void tuongben_wc(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.2, 8.0, 10.0));
	mat4 model_base = model_tuongwc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.87, 0.83, 0.77);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void tuongtruoc_wc(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_tuongwc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.87, 0.83, 0.77);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void tran_wc(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(8.4, 3.8, 10.0));
	mat4 model_base = model_tuongwc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.87, 0.83, 0.77);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void guong_wc(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (float i = 0; i <= 360; i += 0.1) {
		instance = translate(vec3(x, y, z)) * rotate_x(i) * scale(vec3(0.1, 2.5, 2.5));
		mat4 model_base = model_tuongwc * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.75, 1);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void phong_wc(float x, float y, float z, int goc)
{
	model_tuongwc = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.2, 1.2, 1.2));
	tuongsau_wc(0.0, 0, -4.9);		// tường wc sau
	tuongben_wc(4.1, 0, 0);			// tường wc phải
	tuongben_wc(-4.1, 0, 0);			// tường wc trái
	tran_wc(0, 5.9, 0);
	guong_wc(4, 1.2, 1.5);
	tuongtruoc_wc(2.0, 0, 4.9, 4.0, 8.0, 0.2);
	tuongtruoc_wc(-3.5, 0, 4.9, 1.0, 8.0, 0.2);
	tuongtruoc_wc(-1.5, 2.8, 4.9, 3.0, 2.4, 0.2);
}


//===============================CHAU RUA TAY===============================
mat4 model_chaurua, model_view_chaurua;
float crcr[] = { 0,0,0 };
bool nuoc = false;

void day_chaurua(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2.4, 0.2, 4.0));
	mat4 model_base = model_chaurua * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.05, 0.05, 0.81);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanh_chaurua(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_chaurua * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.39, 0.39, 0.81);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ongdannuoc_chaurua(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_chaurua * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.66, 0.66, 0.66);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void voinuoc_chaurua(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_chaurua * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.66, 0.66, 0.66);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void van_voinuoc_chaurua1(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.2, 0.2, 0.1));
	mat4 model_base = model_chaurua * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0, 0.75, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void van_voinuoc_chaurua2(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.1, 0.3, 0.1));
	mat4 model_base = model_chaurua * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0, 0.75, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void nuoc_chaurua(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_chaurua * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.11, 0.56, 1.0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chaurua(float x, float y, float z, int goc)
{
	model_chaurua = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(0.8, 0.8, 0.8));
	day_chaurua(1.4, -2.0, -2.5);

	thanh_chaurua(0.6, -1.7, -2.5, 0.7, 0.4, 4.0);   // thanh trong to hon
	thanh_chaurua(2.45, -1.7, -2.5, 0.3, 0.4, 4.0);	  // thanh truoc be hon
	thanh_chaurua(1.65, -1.7, -0.6, 1.4, 0.4, 0.2);	  // thanh trai 
	thanh_chaurua(1.65, -1.7, -4.4, 1.4, 0.4, 0.2);	  // thanh phai

	ongdannuoc_chaurua(1.4, -2.6, -2.5, 0.3, 1.0, 0.3);  // ống nước dọc
	ongdannuoc_chaurua(0.75, -2.95, -2.5, 1.0, 0.3, 0.3);  // ống nước ngang

	voinuoc_chaurua(0.6, -1.4, -2.5, 0.3, 0.2, 1.2);   // chan de voi nuoc
	voinuoc_chaurua(0.61, -1.05, -2.5, 0.2, 0.5, 0.2);   // thanh doc 1 voi nuoc
	voinuoc_chaurua(1.0, -0.9, -2.5, 0.8, 0.2, 0.2);   // thanh ngang voi nuoc
	voinuoc_chaurua(1.3, -1.1, -2.5, 0.2, 0.2, 0.2);   // thanh doc 2 voi nuoc

	if (nuoc) {
		nuoc_chaurua(1.625, -1.8, -2.5, 1.35, 0.1, 3.6);
		nuoc_chaurua(1.3, -1.25, -2.5, 0.1, 0.1, 0.1);
		nuoc_chaurua(1.3, -1.5, -2.5, 0.1, 0.1, 0.1);
	}
	else nuoc_chaurua(0, 0, 0, 0, 0, 0);
	model_chaurua = model_chaurua * translate(vec3(0.6, -1.35, 0.0)) * rotate_z(crcr[0]) * translate(vec3(-0.6, 1.35, 0.0));
	van_voinuoc_chaurua1(0.6, -1.35, -1.85);
	van_voinuoc_chaurua2(0.6, -1.1, -1.85);
}


//============================BỒN CẦU===============================
mat4 model_bc, model_view_bc;
float bcbc[] = { 0,0,0 };

void Tru_BonCau(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(1.4, 0.8, 2));
	mat4 model_base = model_bc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.6, 0.84, 0.7);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Be_BonCau(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(1.8, 0.4, 3.2));
	mat4 model_base = model_bc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0, 0.84, 0.7);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TruNuoc_BonCau(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(1.4, 1.8, 0.8));
	mat4 model_base = model_bc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.6, 0.84, 0.7);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Chongoi_BonCau(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_bc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.7, 0.58, 0.73);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Nap_BonCau(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(1.8, 0.1, 2));
	mat4 model_base = model_bc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.6, 0.84, 0.7);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Nutxa_BonCau(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.4, 0.1, 0.1));
	mat4 model_base = model_bc * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.5, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void boncau(float x, float y, float z, int goc)
{
	model_bc = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.0, 1.0, 1.0));
	Tru_BonCau(0, 0, 0);
	Be_BonCau(0, 0.6, 0.25);
	TruNuoc_BonCau(0, 1.7, -0.8);
	Chongoi_BonCau(0.7, 0.9, 0.85, 0.4, 0.2, 2.0);
	Chongoi_BonCau(-0.7, 0.9, 0.85, 0.4, 0.2, 2.0);
	Chongoi_BonCau(0, 0.9, 0.15, 1.0, 0.2, 0.6);
	Chongoi_BonCau(0, 0.9, 1.65, 1.0, 0.2, 0.4);
	mat4 model_bc_bandau = model_bc;
	model_bc = model_bc_bandau * translate(vec3(0, 1.05, -0.1)) * rotate_x(bcbc[0]) * translate(vec3(0, -1.05, 0.1));
	Nap_BonCau(0, 1.05, 0.85);

	model_bc = model_bc_bandau * translate(vec3(-0.4, 2.2, 0)) * rotate_z(bcbc[1]) * translate(vec3(0.4, -2.2, 0));
	Nutxa_BonCau(-0.6, 2.2, -0.35);
}


//======================================================
//=====================VÂN ANH=========================
//======================================================
//=========================Hộp đũa========================
mat4 model_hopdua;

void matsau(float x, float y, float z, float x1, float y1, float z1, int r, int g, int b)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_hopdua * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Hopdua(float x, float y, float z, float goc)
{
	model_hopdua = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(0.5, 0.5, 0.5));

	matsau(0, 0, 0, 1, 0.1, 1.5, 1.0, 0.220, 0.125); //đáy
	matsau(-0.5, 0.25, 0, 0.02, 0.5, 1.5, 0.478, 0.220, 0.125); //sau
	matsau(0.5, 0.25, 0, 0.02, 0.5, 1.5, 0.478, 0.220, 0.125); //truoc

	matsau(-0.505, 0.58, 0.51, 0.02, 0.5, 0.45, 0.478, 0.220, 0.125); //canh truoc
	matsau(0.505, 0.58, 0.51, 0.02, 0.5, 0.45, 0.478, 0.220, 0.125); //canh sau

	matsau(0, 0.625, 0.75, 1.0, 1.25, 0.02, 1.0, 0, 0); //trai
	matsau(0, 0.4, 0.3, 1.0, 0.8, 0.02, 0.478, 0.220, 0.125); //vach ngan giua
	matsau(0, 0.25, -0.75, 1.0, 0.5, 0.02, 0.478, 0.220, 0.125); //phai

	matsau(0.1, 0.75, 0.5, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa
	matsau(-0.13, 0.75, 0.43, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa
	matsau(0.3, 0.75, 0.55, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa
	matsau(0.25, 0.75, 0.48, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa
	matsau(-0.3, 0.75, 0.52, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa
	matsau(-0.225, 0.75, 0.4, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa
	matsau(-0.21, 0.75, 0.36, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa
	matsau(0.0, 0.75, 0.5, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa
	matsau(0.25, 0.75, 0.38, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa
	matsau(-0.3, 0.75, 0.49, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa
	matsau(-0.13, 0.75, 0.38, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa
	matsau(0.3, 0.75, 0.41, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa
	matsau(0.25, 0.75, 0.38, 0.05, 1.6, 0.05, 0.753, 0.314, 0.314); //đũa

	matsau(0, 0.05, -0.1, 0.7, 0.1, 0.7, 1, 1, 1); //giấy ăn
	matsau(0, 0.15, -0.1, 0.7, 0.1, 0.7, 1, 1, 1); //giấy ăn
	matsau(0, 0.1, -0.1, 0.7, 0.1, 0.7, 1, 1, 1); //giấy ăn
	matsau(0, 0.25, -0.105, 0.7, 0.1, 0.7, 1, 1, 1); //giấy ăn
	matsau(0, 0.2, -0.1, 0.7, 0.1, 0.7, 1, 1, 1); //giấy ăn

}

void nhieu_hopdua()
{
	Hopdua(5,	-4.475, 3, 90);
	Hopdua(-5,	-4.475, 3, -90);
	Hopdua(5,	-4.475, 10, 90);
	Hopdua(-5,	-4.475, 10, -90);
	Hopdua(5,	-4.475, -4, 90);
	Hopdua(-5,	-4.475, -4, -90);
}


//=========================Thung rac========================
mat4 model_thungrac, model_view_thungrac;
float thungrac[] = { 0,0,0 };

void truthungrac(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.7, 1.0, 0.9));
	mat4 model_base = model_thungrac * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.624, 0.878, 0.894);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void Nap_thungrac(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.7, 0.1, 1.0));
	mat4 model_base = model_thungrac * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.294, 0.702, 0.8);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Nutbat_thrac(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.3, 0.1, 0.2));
	mat4 model_base = model_thungrac * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.294, 0.702, 0.8);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void caithungrac(float x, float y, float z, float goc)
{
	model_thungrac = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(0.8, 0.8, 0.8));
	truthungrac(0.0, -2.8, 0.0);
	Nutbat_thrac(0.0, -3.1, -0.5);
	model_thungrac = model_thungrac * translate(vec3(0.0, -2.25, 0.5)) * rotate_x(thungrac[0]) * translate(vec3(0.0, 2.25, -0.5));
	Nap_thungrac(0.0, -2.25, 0.0);

}

void nhieu_thungrac()
{
	caithungrac(4,	-4.36, 3.0, 90);
	caithungrac(-4, -4.36, 3.0, -90);
	caithungrac(4,	-4.36, 10.0, 90);
	caithungrac(-4, -4.36, 10.0, -90);
	caithungrac(4,	-4.36, -4.0, 90);
	caithungrac(-4, -4.36, -4.0, -90);
}

//===================================Người================================
mat4 model_nguoi;
float ngng[] = { 0, 0, 0 };

void body(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_nguoi * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.46, 0.71, 0.81);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void upper_leg(float x, float y, float z, float x1, float y1, float z1, float r, float g, float b)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_nguoi * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void upper_arm(float x, float y, float z, float x1, float y1, float z1, float r, float g, float b)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_nguoi * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void neck(float x, float y, float z, float x1, float y1, float z1, float r, float g, float b)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_nguoi * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void head(float x, float y, float z, float x1, float y1, float z1, float r, float g, float b)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_nguoi * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Robot(float x, float y, float z, float goc)
{
	model_nguoi = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.5, 1.5, 1.5));
	body(0, 0, 0, 1, 1.6, 0.4);
	neck(0, 0.9, 0, 0.2, 0.2, 0.2, 1, 0.8, 0.76);

	mat4 model_nguoi_bandau = model_nguoi;
	model_nguoi = model_nguoi_bandau * translate(vec3(0, 1.2, 0)) * rotate_z(ngng[0]) * translate(vec3(0, -1.2, 0));
	head(0, 1.3, 0, 0.6, 0.6, 0.4, 1, 0.8, 0.76);

	model_nguoi = model_nguoi_bandau * translate(vec3(0.3, -1.0, 0)) * rotate_x(ngng[1]) * translate(vec3(0.3, 1.0, 0));
	upper_leg(-0.3, -1.0, 0, 0.4, 0.4, 0.2, 0.46, 0.71, 0.81);
	upper_leg(-0.3, -1.6, 0, 0.2, 0.8, 0.16, 1, 0.8, 0.76);
	model_nguoi = model_nguoi_bandau * translate(vec3(0.3, -1.0, 0)) * rotate_x(-ngng[1]) * translate(vec3(0.3, 1.0, 0));
	upper_leg(-0.9, -1.0, 0, 0.4, 0.4, 0.2, 0.46, 0.71, 0.81);
	upper_leg(-0.9, -1.6, 0, 0.2, 0.8, 0.16, 1, 0.8, 0.76);
	model_nguoi = model_nguoi_bandau * translate(vec3(0.0, 0.6, 0)) * rotate_x(-ngng[1]) * translate(vec3(0.0, -0.6, 0));
	upper_arm(0.65, 0.6, 0, 0.3, 0.4, 0.16, 0.46, 0.71, 0.81);
	upper_arm(0.65, 0.1, 0, 0.2, 0.6, 0.14, 1, 0.8, 0.76);
	model_nguoi = model_nguoi_bandau * translate(vec3(0.0, 0.6, 0)) * rotate_x(ngng[1]) * translate(vec3(0.0, -0.6, 0));
	upper_arm(-0.65, 0.6, 0, 0.3, 0.4, 0.16, 0.46, 0.71, 0.81);
	upper_arm(-0.65, 0.1, 0, 0.2, 0.6, 0.14, 1, 0.8, 0.76);
}

void nhieu_nguoi()
{
	Robot(0, -4, 0, 0);
	
}

////===================================Đồng hồ================================
mat4 model_dongho;
float dhdh[] = {0, 0, 0};

void mat_dongho(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(1.0, 1.0, 0.2));
	mat4 model_base = model_dongho * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.8, 1);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void gio12(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance =  translate(vec3(x, y, z)) * scale(vec3(0.05, 0.2, 0.05));
	mat4 model_base = model_dongho * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void gio3(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = rotate_z(-90) * translate(vec3(x, y, z)) * scale(vec3(0.05, 0.2, 0.05));
	mat4 model_base = model_dongho * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void gio6(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = rotate_z(-180) * translate(vec3(x, y, z)) * scale(vec3(0.05, 0.2, 0.05));
	mat4 model_base = model_dongho * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void gio9(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = rotate_z(-270) * translate(vec3(x, y, z)) * scale(vec3(0.05, 0.2, 0.05));
	mat4 model_base = model_dongho * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void kimDongHo()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 0.2, -0.125)) * scale(vec3(0.05, 0.4, 0.05));
	mat4 model_base = model_dongho * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void dongho(float x, float y, float z, int goc)
{
	model_dongho = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.5, 1.5, 1.5));
	mat_dongho(0, 0, 0);
	gio12(0.0, 0.35, -0.125);
	gio3(0.0, 0.35, -0.125);
	gio6(0.0, 0.35, -0.125);
	gio9(0.0, 0.35, -0.125);
	model_dongho = model_dongho * rotate_z(dhdh[0]);
	kimDongHo();
}

////=================================== Bát đĩa ================================
mat4 model_batdia;
float batdia[] = { 0,0,0 };
int bd = 0;


void dia_tron(float x, float y, float z, float goc, float cao, float r, float g, float b) {
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {
		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(goc, cao, 0.1));
		mat4 model_base = model_batdia * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
void bat_tron(float x, float y, float z, float outer_radius, float inner_radius, float height, float r, float g, float b) 
{
	int num_segments = 20; // Số lượng phân đoạn để vẽ hình tròn
	// Vẽ bề mặt bên ngoài
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {
		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(outer_radius, height, 0.1));
		mat4 model_base = model_batdia * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// Vẽ bề mặt bên trong
	mat4 inner_instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {
		inner_instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(inner_radius, height, 0.1));
		mat4 model_base_inner = model_batdia * inner_instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base_inner.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.9, 0.8, 0.7);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
void doi_dua(float x, float y, float z, float x1, float y1, float z1, int r, int g, int b)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_batdia * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void bat_dia(float x, float y, float z, int goc)
{
	model_batdia = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(0.2, 0.2, 0.2));;

	// Đặt đĩa lớn hơn lên bàn
	dia_tron(0.0, 0.1, 0.0, 3.0, 0.05, 1.0, 1.0, 1.0);  // Đĩa màu trắng lớn

	// Đặt bát rỗng lên đĩa
	bat_tron(0.0, 0.38, 0.0, 2.0, 1.6, 0.5, 0.58, 0.9, 1);  // Bát màu ngà rỗng

	// Đũa
	doi_dua(0, 0.7, 0, 3.6, 0.05, 0.05, 0.753, 0.314, 0.314); //đũa
	doi_dua(0, 0.7, 0.2, 3.6, 0.05, 0.05, 0.753, 0.314, 0.314); //đũa
}
void nhieu_batdia()
{
	bat_dia(3, -4.5, -4, 0);
	//bat_dia(5.0, 0, 0, 0);
}


//======================================================
//=======================DƯƠNG==========================
//======================================================
//============================BAN_GHE===============================
mat4 model_ban, model_view_ban;

void mat_ban(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ban * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.68, 0.5, 0.37);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chan_ban(float x, float y, float z, float x1, float y1, float z1) 
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ban * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.68, 0.5, 0.37);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ban(float x, float y, float z, int goc)
{
	model_ban = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1, 1, 1));
	mat_ban(0.0, 0.0, 0.0, 2.4, 0.1, 3.4);
	chan_ban(0.9, -1.2, 1.4, 0.2, 2.5, 0.2);
	chan_ban(0.9, -1.2, -1.4, 0.2, 2.5, 0.2);
	chan_ban(-0.9, -1.2, 1.4, 0.2, 2.5, 0.2);
	chan_ban(-0.9, -1.2, -1.4, 0.2, 2.5, 0.2);
}

//-------------------ghe--------------------
mat4 model_ghe, model_view_ghe;
float gg[] = { 0, 0, 0 };

void mat_ghe(float x, float y, float z, float x1, float y1, float z1) 
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ghe * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1, 0.82, 0.35);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chan_ghe(float x, float y, float z, float x1, float y1, float z1) 
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ghe * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.2, 0.2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void tua_ghe(float x, float y, float z, float x1, float y1, float z1) {
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ghe * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1, 0.82, 0.35);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ghe(float x, float y, float z, int goc)
{
	model_ghe = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1, 1, 1));
	model_ghe = model_ghe * translate(vec3(gg[0], 0, 0));
	mat_ghe(0.0, 0.0, 0.0, 1.5, 0.1, 1.0);
	chan_ghe(0.65, -1.05, 0.4, 0.2, 2.0, 0.2);
	chan_ghe(0.65, -1.05, -0.4, 0.2, 2.0, 0.2);
	chan_ghe(-0.65, -1.05, 0.4, 0.2, 2.0, 0.2);
	chan_ghe(-0.65, -1.05, -0.4, 0.2, 2.0, 0.2);
	tua_ghe(-0.675, 0.75, 0, 0.15, 1.5, 1.0);
}

void ban_ghe() {
	//Ban1
	ban(-4, -4.55, -4.0, 90);
	ghe(-3.25, -4.95, -6.5, -90);
	ghe(-3.25, -4.95, -1.5, 90);
	ghe(-4.75, -4.95, -6.5, -90);
	ghe(-4.75, -4.95, -1.5, 90);

	// Bàn 2 
	ban(-4, -4.55, 3.0, 90);
	ghe(-3.25, -4.95, 0.5, -90);
	ghe(-3.25, -4.95, 5.5, 90);
	ghe(-4.75, -4.95, 0.5, -90);
	ghe(-4.75, -4.95, 5.5, 90);

	// Bàn 3
	ban(-4, -4.55, 10.0, 90);
	ghe(-3.25, -4.95, 7.5, -90);
	ghe(-3.25, -4.95, 12.5, 90);
	ghe(-4.75, -4.95, 7.5, -90);
	ghe(-4.75, -4.95, 12.5, 90);

	// Bàn 4
	ban(4.0, -4.55, -4.0, 90);
	ghe(4.75, -4.95, -6.5, -90);
	ghe(4.75, -4.95, -1.5, 90);
	ghe(3.25, -4.95, -6.5, -90);
	ghe(3.25, -4.95, -1.5, 90);

	// Bàn 5 
	ban(4.0, -4.55, 3.0, 90);
	ghe(4.75, -4.95, 0.5, -90);
	ghe(4.75, -4.95, 5.5, 90);
	ghe(3.25, -4.95, 0.5, -90);
	ghe(3.25, -4.95, 5.5, 90);

	// Bàn 6
	ban(4.0, -4.55, 10.0, 90);
	ghe(4.75, -4.95, 7.5, -90);
	ghe(4.75, -4.95, 12.5, 90);
	ghe(3.25, -4.95, 7.5, -90);
	ghe(3.25, -4.95, 12.5, 90);
}

//============================CUA CHINH===============================
mat4 model_cuachinh;
float chch[] = { 0, 0, 0 };


void khung_cuachinh(float x, float y, float z, float x1, float y1, float z1) 
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_cuachinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.7, 0.7, 0.7);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanh_doc(float x, float y, float z, float x1, float y1, float z1) 
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_cuachinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0, 1.0, 1.0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void tay_nam(float x, float y, float z, float x1, float y1, float z1) 
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_cuachinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.2, 0.2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void cuachinh(float x, float y, float z, int goc)
{
	model_cuachinh = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.5, 1.5, 1.5));;
	model_cuachinh = model_cuachinh * translate(vec3(1.5, 0, 0)) * rotate_y(chch[0]) * translate(vec3(-1.5, 0, 0));
	khung_cuachinh(0, 0.0, 0.0, 3.0, 6.0, 0.2);
	for (int i = -2; i <= 2; ++i) {
		thanh_doc(i * 0.5, 0, -0.2, 0.1, 6.0, 0.1);
	}
	tay_nam(-0.8, 0, -0.2, 0.1, 1.0, 0.1);
}



//============================DIEU HOA===============================
mat4 model_dieu_hoa;
float Beta = 0.0;

void than_dieu_hoa(float x, float y, float z, float x1, float y1, float z1) 
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_dieu_hoa * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.99, 0.94, 0.88);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void cua_gio(float x, float y, float z, float x1, float y1, float z1) 
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_dieu_hoa * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.7, 0.7, 0.71);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void banh_rang(float x, float y, float z, float radius, float width, int teeth) 
{
	float angle_step = 360.0 / teeth;
	for (int i = 0; i < teeth; ++i) {
		float angle = i * angle_step;
		mat4 instance = identity_mat4();
		instance = translate(vec3(x, y, z)) * rotate_z(angle) * scale(vec3(radius, width, radius / teeth));
		mat4 model_base = model_dieu_hoa * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.39, 0.39, 0.39);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void man_hinh(GLfloat x, GLfloat y, GLfloat z, GLfloat x1, GLfloat y1) 
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, 0.01f));
	mat4 model_base = model_dieu_hoa * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.59, 0.86, 0.84);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void dieuhoa(float x, float y, float z, int goc)
{
	model_dieu_hoa = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1, 1, 1));
	than_dieu_hoa(0.0, 0.0, 0.0, 6.0, 1.5, 1.0);
	man_hinh(2.7, 0.5, 0.51, 0.5, 0.2);
	
	model_dieu_hoa = model_dieu_hoa * translate(vec3(0.0, -0.6, 0.55)) * rotate_x(Beta) * translate(vec3(0.0, 0.6, -0.55));
	cua_gio(0.0, -0.7, 0.55, 5.0, 0.5, 0.2);
	banh_rang(-2.0, -0.7, 0.4, 0.3, 0.1, 20);
	banh_rang(-1.0, -0.7, 0.4, 0.3, 0.1, 20);
	banh_rang(0.0, -0.7, 0.4, 0.3, 0.1, 20);
	banh_rang(0.0, -0.7, 0.4, 0.3, 0.1, 20);
	banh_rang(1.0, -0.7, 0.4, 0.3, 0.1, 20);
	banh_rang(2.0, -0.7, 0.4, 0.3, 0.1, 20);
}

void nhieu_dieuhoa()
{
	dieuhoa(9.3, 3, -2, -90);
	dieuhoa(9.3, 3, 9, -90);
}





//======================================================
//=======================HUYỀN==========================
//======================================================
//============================CỬA SỔ===============================
mat4 model_cuaso_trai, model_cuaso_phai;
float cst[] = { 0, 0, 0 };
float csp[] = { 0, 0, 0 };

void khungtrenduoi_cuaso_trai(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2.0, 0.5, 0.2));
	mat4 model_base = model_cuaso_trai * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.2, 0.2);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void khungtraiphai_cuaso_trai(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.3, 3.0, 0.2));
	mat4 model_base = model_cuaso_trai * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.2, 0.2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void kinh_cuaso_trai(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(1.4, 3.0, 0.2));
	mat4 model_base = model_cuaso_trai * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.8, 0.9, 0.89);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void cuasotrai(float x, float y, float z, int goc)
{
	model_cuaso_trai = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.0, 1.0, 1.0));

	model_cuaso_trai = model_cuaso_trai * translate(vec3(2.0, 0, 0)) * rotate_y(cst[0]) * translate(vec3(-1.0, 0, 0));

	khungtrenduoi_cuaso_trai(0, 0, 0);			// thanh duoi
	kinh_cuaso_trai(0, 1.75, 0);
	khungtrenduoi_cuaso_trai(0, 3.5, 0);					// thanh tren
	khungtraiphai_cuaso_trai(0.85, 1.75, 0);
	khungtraiphai_cuaso_trai(-0.85, 1.75, 0);
}

void khungtrenduoi_cuaso_phai(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2.0, 0.5, 0.2));
	mat4 model_base = model_cuaso_phai * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.2, 0.2);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void khungtraiphai_cuaso_phai(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.3, 3.0, 0.2));
	mat4 model_base = model_cuaso_phai * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.2, 0.2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void kinh_cuaso_phai(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(1.4, 3.0, 0.2));
	mat4 model_base = model_cuaso_phai * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.8, 0.9, 0.89);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void cuasophai(float x, float y, float z, int goc)
{
	model_cuaso_phai = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.0, 1.0, 1.0));

	model_cuaso_phai = model_cuaso_phai * translate(vec3(-2.0, 0, 0)) * rotate_y(csp[0]) * translate(vec3(1.0, 0, 0));

	khungtrenduoi_cuaso_phai(0, 0, 0);			// thanh duoi
	kinh_cuaso_phai(0, 1.75, 0);
	khungtrenduoi_cuaso_phai(0, 3.5, 0);					// thanh tren
	khungtraiphai_cuaso_phai(0.85, 1.75, 0);
	khungtraiphai_cuaso_phai(-0.85, 1.75, 0);
}

void cuaso(float x, float y, float z, int goc)
{
	cuasotrai(x, y, z, goc);
	cuasophai(x, y, z, goc);
}

//============================BỒN RỬA BÁT===============================
mat4 model_chauruabat;
float crb[] = { 0,0,0 };

void chanchau(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2, 3, 0.2));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.2, 0.2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void matchaurua(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2, 0.2, 1));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.37, 0.37, 0.37);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void canhdocchau1(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(1.4, 1, 0.1));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.75, 0.75, 0.75);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void canhngangchau1(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.1, 1, 1.1));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.75, 0.75, 0.75);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void day_chaurua1(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(1.4, 0.1, 1));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.75, 0.75, 0.75);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanhngangtruoc_chau1(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.2, 0.2, 1.2));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.37, 0.37, 0.37);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanhgiua_chaurua(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2, 0.2, 0.2));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.37, 0.37, 0.37);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanhngangchau(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.25, 3.1, 4.35));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.37, 0.37, 0.37);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanhdoc_voinuoc1(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.1, 1, 0.1));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.75, 0.75, 0.75);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanhngang_voinuoc1(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.1, 0.1, 0.3));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.75, 0.75, 0.75);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanhdocngan_voinuoc1(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.1, 0.1, 0.05));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.75, 0.75, 0.75);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanhngang_nut1(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.05, 0.05, 0.1));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.75, 0.75);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void thanhdoc_nut1(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.05, 0.3, 0.05));
	mat4 model_base = model_chauruabat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.75, 0.75);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void bonruabat(float x, float y, float z, int goc)
{
	model_chauruabat = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.0, 1.0, 1.0));
	//==========CHAU RUA BAT============
	chanchau(0, -3, -0.35);
	matchaurua(0, -1.4, 0);
	canhdocchau1(0, -1.825, 0.55);
	canhngangchau1(0.75, -1.825, 1.025);
	canhdocchau1(0, -1.825, 1.525);
	canhngangchau1(-0.75, -1.825, 1.025);
	day_chaurua1(0, -2.325, 1.05);
	thanhngangtruoc_chau1(-0.9, -1.4, 1.01);

	canhdocchau1(0, -1.825, 1.8);
	canhngangchau1(0.75, -1.825, 2.3);
	canhdocchau1(0, -1.825, 2.8);
	canhngangchau1(-0.75, -1.825, 2.3);
	day_chaurua1(0, -2.325, 2.3);
	thanhngangtruoc_chau1(-0.9, -1.4, 2.3);

	thanhgiua_chaurua(0, -1.4, 1.63);
	thanhngangchau(0.9, -2.85, 1.68);

	matchaurua(0, -1.4, 3.35);
	chanchau(0, -3, 3.7);
	//===========VOI NUOC==========
	// VOI 1
	thanhdoc_voinuoc1(0.55, -0.8, 0.45);
	thanhngang_voinuoc1(0.55, -0.3, 0.6);
	thanhdocngan_voinuoc1(0.55, -0.4, 0.7);
	// VOI 2
	thanhdoc_voinuoc1(0.55, -0.8, 1.6);
	thanhngang_voinuoc1(0.55, -0.3, 1.7);
	thanhdocngan_voinuoc1(0.55, -0.4, 1.8);

	mat4 model_chauruabat_bandau = model_chauruabat;
	model_chauruabat = model_chauruabat_bandau * translate(vec3(0, -1, 0.45)) * rotate_x(crb[0]) * translate(vec3(0, 1, -0.45));

	thanhngang_nut1(0.48, -1, 0.45);
	thanhdoc_nut1(0.48, -0.85, 0.45);

	model_chauruabat = model_chauruabat_bandau * translate(vec3(0, -1, 1.6)) * rotate_x(crb[0]) * translate(vec3(0, 1, -1.6));
	thanhngang_nut1(0.48, -1, 1.6);
	thanhdoc_nut1(0.48, -0.85, 1.6);
}

//============================TỦ BÁT===============================
mat4 model_tubat;
float trb[] = { 0,0,0 };

void day_turb(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2.4, 0.1, 1.4));
	mat4 model_base = model_tubat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.40, 0.27, 0.21);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void canh_turb(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.1, 1.4, 1.4));
	mat4 model_base = model_tubat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.40, 0.27, 0.21);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void canhsau_turb(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2.4, 1.4, 0.1));
	mat4 model_base = model_tubat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.42, 0.30, 0.19);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void canhgiua_turb(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.1, 1.2, 1.4));
	mat4 model_base = model_tubat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.40, 0.27, 0.21);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//=====đĩa====
void matdia(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {

		instance = translate(vec3(x, y, z)) * rotate_x(i) * scale(vec3(0.04, 0.5, 0.1));
		mat4 model_base = model_tubat * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1, 1, 1);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
void daydia(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {

		instance = translate(vec3(x, y, z)) * rotate_x(i) * scale(vec3(0.02, 0.2, 0.2));
		mat4 model_base = model_tubat * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.5, 0.5);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
void dia(float x, float y, float z)
{
	//dia1
	matdia(1.18, -0.35, 0);
	daydia(1.15, -0.37, 0);
	//dia2
	matdia(1.08, -0.35, 0);
	daydia(1.05, -0.37, 0);
	//dia3
	matdia(0.98, -0.35, 0);
	daydia(0.95, -0.37, 0);
	//dia4
	matdia(0.88, -0.35, 0);
	daydia(0.85, -0.37, 0);
	//dia5
	matdia(0.78, -0.35, 0);
	daydia(0.75, -0.37, 0);
	//dia6
	matdia(0.68, -0.35, 0);
	daydia(0.65, -0.37, 0);
	//dia7
	matdia(0.58, -0.35, 0);
	daydia(0.55, -0.37, 0);
	//dia8
	matdia(0.48, -0.35, 0);
	daydia(0.45, -0.37, 0);
	//dia9
	matdia(0.38, -0.35, 0);
	daydia(0.35, -0.37, 0);
	//dia10
	matdia(0.28, -0.35, 0);
	daydia(0.25, -0.37, 0);
	//dia11
	matdia(0.18, -0.35, 0);
	daydia(0.15, -0.37, 0);
	//dia12
	matdia(-0.12, -0.35, 0);
	daydia(-0.15, -0.37, 0);
	//dia13
	matdia(-0.22, -0.35, 0);
	daydia(-0.25, -0.37, 0);
	//dia14
	matdia(-0.32, -0.35, 0);
	daydia(-0.35, -0.37, 0);
	//dia15
	matdia(-0.42, -0.35, 0);
	daydia(-0.45, -0.37, 0);
	//dia16
	matdia(-0.52, -0.35, 0);
	daydia(-0.55, -0.37, 0);
	//dia17
	matdia(-0.62, -0.35, 0);
	daydia(-0.65, -0.37, 0);
	//dia18
	matdia(-0.72, -0.35, 0);
	daydia(-0.75, -0.37, 0);
	//dia19
	matdia(-0.82, -0.35, 0);
	daydia(-0.85, -0.37, 0);
	//dia20
	matdia(-0.92, -0.35, 0);
	daydia(-0.95, -0.37, 0);
	//dia21
	matdia(-1.02, -0.35, 0);
	daydia(-1.05, -0.37, 0);
	//dia22
	matdia(-1.12, -0.35, 0);
	daydia(-1.15, -0.37, 0);
}
//=========== cửa tủ=========
void canhtrai_turb(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(1.15, 1.2, 0.1));
	mat4 model_base = model_tubat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.96, 0.93, 0.82);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void taynamtrb_trai(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {

		instance = translate(vec3(x, y, z)) * rotate_z(i) * scale(vec3(0.04, 0.15, 0.1));
		mat4 model_base = model_tubat * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.23, 0.23, 0.21);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
void canhphai_turb(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(1.15, 1.2, 0.1));
	mat4 model_base = model_tubat * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.96, 0.93, 0.82);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void taynamtrb_phai(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {

		instance = translate(vec3(x, y, z)) * rotate_z(i) * scale(vec3(0.04, 0.15, 0.1));
		mat4 model_base = model_tubat * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.23, 0.23, 0.21);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void tubat(float x, float y, float z, int goc)
{
	model_tubat = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.8, 1.8, 1.8));
	day_turb(0, 0.65, 0);
	dia(0, 0, 0);
	canh_turb(-1.25, 0, 0);
	canhgiua_turb(0, 0, 0);
	canh_turb(1.25, 0, 0);
	day_turb(0, -0.65, 0);
	canhsau_turb(0, 0, 0.65);

	mat4 model_tubat_bandau = model_tubat;
	model_tubat = model_tubat_bandau * translate(vec3(1.25, 0, -0.65)) * rotate_y(-trb[0]) * translate(vec3(-1.25, 0, 0.65));
	canhtrai_turb(0.625, 0, -0.65);
	taynamtrb_trai(0.2, 0, -0.75);
	model_tubat = model_tubat_bandau * translate(vec3(-1.25, 0, -0.65)) * rotate_y(trb[0]) * translate(vec3(1.25, 0, 0.65));
	canhphai_turb(-0.625, 0, -0.65);
	taynamtrb_phai(-0.2, 0, -0.75);
}

//======================================================
//=======================HÙNG===========================
//======================================================
//===============================BAN BẾP===============================
mat4 model_bep;

void chantraitruoc() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.39, -0.21, 0.19)) * scale(vec3(0.02, 0.4, 0.02));
	mat4 model_chantrai1 = model_bep * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chantrai1.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0f, 0.4f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chantraisau() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.39, -0.21, -0.19)) * scale(vec3(0.02, 0.4, 0.02));
	mat4 model_chantrai2 = model_bep * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chantrai2.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0f, 0.4f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chanphaitruoc() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.39, -0.21, 0.19)) * scale(vec3(0.02, 0.4, 0.02));
	mat4 model_chanphai1 = model_bep * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chanphai1.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0f, 0.4f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chanphaisau() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.39, -0.21, -0.19)) * scale(vec3(0.02, 0.4, 0.02));
	mat4 model_chanphai2 = model_bep * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chanphai2.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0f, 0.4f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void matban() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 0.0, 0.0)) * scale(vec3(0.8, 0.02, 0.4));
	mat4 model_chantrai2 = model_bep * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chantrai2.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0f, 0.75f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void banbep(float x, float y, float z, int goc)
{
	model_bep = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(8.0, 8.0, 5.0));
	chantraitruoc();
	chantraisau();
	chanphaitruoc();
	chanphaisau();
	matban();
}
//===============================BẾP GAS===============================
mat4 model_bepgas;
float bgbg[] = { 0, 0, 0 };

//====================thân bếp====================

void thanbep() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 0.025, 0.0)) * scale(vec3(0.4, 0.05, 0.2));
	mat4 model_bepga = model_bepgas * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.4f, 0.5f, 0.3f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void thanhtruoc() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 0.005, 0.125)) * scale(vec3(0.4, 0.01, 0.05));
	mat4 model_bepga = model_bepgas * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0f, 0.5f, 0.7f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void num1() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.14, 0.01, 0.125)) * rotate_y(bgbg[0]) * scale(vec3(0.01, 0.01, 0.02));
	mat4 model_bepga = model_bepgas * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void num2() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.14, 0.01, 0.125)) * rotate_y(bgbg[1]) * scale(vec3(0.01, 0.01, 0.02));
	mat4 model_bepga = model_bepgas * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1, 1, 1);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//====================gác bếp====================

void gac1(float x, float y, float z) {
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.01, 0.01, 0.02));
	mat4 model_bepga = model_bepgas * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.0f, 0.2f, 0.6f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void gac2(float x, float y, float z) {
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.01, 0.01, 0.02));
	mat4 model_bepga = model_bepgas * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.0f, 0.2f, 0.6f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void gac3(float x, float y, float z) {
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.02, 0.01, 0.01));
	mat4 model_bepga = model_bepgas * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.0f, 0.2f, 0.6f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void gac4(float x, float y, float z) {
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.02, 0.01, 0.01));
	mat4 model_bepga = model_bepgas * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.0f, 0.2f, 0.6f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void bepgas(float x, float y, float z, int goc)
{
	model_bepgas = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(8.0, 8.0, 8.0));
	thanbep();
	thanhtruoc();
	num1();
	num2();
	// phai
	gac1(-0.14, 0.055, -0.035);
	gac2(-0.14, 0.055, 0.035);
	gac3(-0.105, 0.055, 0);
	gac4(-0.175, 0.055, 0);
	// trai
	gac1(0.14, 0.055, -0.035);
	gac2(0.14, 0.055, 0.035);
	gac3(0.105, 0.055, 0);
	gac4(0.175, 0.055, 0);
}


//====================xoong====================
mat4 model_xoong;
void mattrai() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.19, 0.13, 0.035)) * scale(vec3(0.02, 0.09, 0.16));
	mat4 model_bepga = model_xoong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2f, 0.3f, 0.4f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void matphai() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.015, 0.13, 0.035)) * scale(vec3(0.02, 0.09, 0.16));
	mat4 model_bepga = model_xoong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2f, 0.3f, 0.4f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void mattruoc() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.1, 0.13, 0.115)) * scale(vec3(0.16, 0.09, 0.02));
	mat4 model_bepga = model_xoong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2f, 0.3f, 0.4f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void matsau() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.1, 0.13, -0.045)) * scale(vec3(0.16, 0.09, 0.02));
	mat4 model_bepga = model_xoong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2f, 0.3f, 0.4f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void matduoi() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.1, 0.08, 0.035)) * scale(vec3(0.18, 0.02, 0.18));
	mat4 model_bepga = model_xoong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2f, 0.3f, 0.4f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void taynam1() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.21, 0.165, 0.035)) * scale(vec3(0.02, 0.02, 0.04));
	mat4 model_bepga = model_xoong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.7f, 0.4f, 0.3f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void taynam2() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.005, 0.165, 0.035)) * scale(vec3(0.02, 0.02, 0.04));
	mat4 model_bepga = model_xoong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_bepga.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.7f, 0.4f, 0.3f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void xoong(float x, float y, float z, int goc) {
	model_xoong = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(4.0, 4.0, 4.0));
	taynam2();
	matduoi();
	mattrai();
	matphai();
	mattruoc();
	matsau();
	taynam1();
}

//========================NỒI PHỞ====================================
mat4 model_noipho;
float npnp[] = { 0, 0, 0 };

void channoi(float x, float y, float z) {
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.02, 0.1, 0.02));
	mat4 noipho = model_noipho * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, noipho.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0f, 0.4f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void daynoi() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 0.0, 0.0)) * scale(vec3(0.4, 0.06, 0.4));
	mat4 noipho = model_noipho * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, noipho.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0f, 0.75f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void mattraiphainoi(float x, float y, float z) {
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.02, 0.3, 0.2));
	mat4 noipho = model_noipho * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, noipho.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2f, 0.75f, 0.2f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void mattruocsaunoi(float x, float y, float z) {
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.2, 0.3, 0.02));
	mat4 noipho = model_noipho * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, noipho.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2f, 0.75f, 0.2f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void numvan1() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.03, 0, 0.21)) * rotate_z(npnp[0]) * scale(vec3(0.02, 0.01, 0.01));
	mat4 noipho = model_noipho * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, noipho.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.4f, 0.75f, 0.2f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void numvan2() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.03, 0, 0.21)) * rotate_z(npnp[0]) * scale(vec3(0.02, 0.01, 0.01));
	mat4 noipho = model_noipho * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, noipho.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.4f, 0.75f, 0.2f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void noipho(float x, float y, float z, int goc)
{
	model_noipho = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(5.0, 5.0, 5.0));
	daynoi();
	channoi(-0.19, -0.08, 0.19);
	channoi(-0.19, -0.08, -0.19);
	channoi(0.19, -0.08, -0.19);
	channoi(0.19, -0.08, 0.19);
	mattraiphainoi(-0.1, 0.175, 0.0);
	mattraiphainoi(0.1, 0.175, 0.0);
	mattruocsaunoi(0, 0.175, -0.1);
	mattruocsaunoi(0, 0.175, 0.1);
	numvan1();
	numvan2();
}

//========================TỦ ĐÔNG====================================
mat4 model_tudong;
float tdtd[] = { 0,0,0 };

void matsau_tudong() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0, 0)) * scale(vec3(0.8, 0.4, 0.02));
	mat4 tudong = model_tudong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.81, 0.91, 0.96);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void mattruoc_tudong() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0, 0.42)) * scale(vec3(0.8, 0.4, 0.02));
	mat4 tudong = model_tudong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.81, 0.91, 0.96);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void matphai_tudong() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.39, 0, 0.21)) * scale(vec3(0.02, 0.4, 0.4));
	mat4 tudong = model_tudong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.81, 0.91, 0.96);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void mattrai_tudong() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.39, 0, 0.21)) * scale(vec3(0.02, 0.4, 0.4));
	mat4 tudong = model_tudong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.81, 0.91, 0.96);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void matduoi_tudong() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, -0.21, 0.21)) * scale(vec3(0.8, 0.02, 0.44));
	mat4 tudong = model_tudong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.81, 0.91, 0.96);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void naptrai_tudong() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.2, 0.21, 0.01)) * rotate_x(tdtd[0]) * translate(vec3(0, 0, 0.2)) * scale(vec3(0.4, 0.02, 0.44));
	mat4 tudong = model_tudong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.49, 0.62, 0.76);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void napphai_tudong() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.2, 0.21, 0.01)) * rotate_x(tdtd[1]) * translate(vec3(0, 0, 0.2)) * scale(vec3(0.4, 0.02, 0.44));
	mat4 tudong = model_tudong * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.49, 0.62, 0.76);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void tudong(float x, float y, float z, int goc) {
	model_tudong = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(6.0, 6.0, 6.0));
	matsau_tudong();
	mattruoc_tudong();
	matphai_tudong();
	mattrai_tudong();
	matduoi_tudong();
	naptrai_tudong();
	napphai_tudong();
}
//==========================BẢNG HIỆU==========================
mat4 model_banghieu;

void nenbanghieu() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0, 0.02)) * scale(vec3(2.0, 0.6, 0.02));
	mat4 model_base = model_banghieu * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.99, 0.51, 0.26);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//===========chữ P==========
void thanhPgiua() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.3, 0.0, 0.0)) * scale(vec3(0.16, 0.05, 0.02));
	mat4 model_chuP = model_banghieu * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chuP.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.19, 0.19);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void thanhPphaitren() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.2, 0.11, 0.0)) * scale(vec3(0.05, 0.18, 0.02));
	mat4 model_chuP = model_banghieu * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chuP.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.19, 0.19);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void thanhPtrai()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.4, 0.0, 0.0)) * scale(vec3(0.05, 0.4, 0.02));
	mat4 model_chuP = model_banghieu * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chuP.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.19, 0.19);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void thanhPtren()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.3, 0.225, 0.0)) * scale(vec3(0.22, 0.05, 0.02));
	mat4 model_chuP = model_banghieu * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chuP.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.19, 0.19);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chuP() {
	thanhPtrai();
	thanhPtren();
	thanhPgiua();
	thanhPphaitren();
}

//===========chữ H==========
void thanhHtrai()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.10, 0.025, 0.0)) * scale(vec3(0.05, 0.45, 0.02));
	mat4 model_chuH = model_banghieu * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chuH.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.19, 0.19);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void thanhHphai()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.10, 0.025, 0.0)) * scale(vec3(0.05, 0.45, 0.02));
	mat4 model_chuH = model_banghieu * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chuH.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.19, 0.19);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void thanhHgiua() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0.025, 0.0)) * scale(vec3(0.16, 0.05, 0.02));
	mat4 model_chuH = model_banghieu * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chuH.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.19, 0.19);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chuH() {
	thanhHtrai();
	thanhHphai();
	thanhHgiua();
}
//================chu 0==============
void thanhOtrai()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.2, 0.025, 0.0)) * scale(vec3(0.05, 0.35, 0.02));
	mat4 model_chuQ = model_banghieu * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chuQ.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.19, 0.19);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void thanhOphai()
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.4, 0.025, 0.0)) * scale(vec3(0.05, 0.35, 0.02));
	mat4 model_chuQ = model_banghieu * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chuQ.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.19, 0.19);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void thanhOtren() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.3, 0.225, 0.0)) * scale(vec3(0.22, 0.05, 0.02));
	mat4 model_chuQ = model_banghieu * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chuQ.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.19, 0.19);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void thanhOduoi() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.3, -0.175, 0.0)) * scale(vec3(0.22, 0.05, 0.02));
	mat4 model_chuQ = model_banghieu * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_chuQ.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.19, 0.19);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chuO() {
	thanhOtrai();
	thanhOphai();
	thanhOtren();
	thanhOduoi();
}

void banghieu(float x, float y, float z, int goc)
{
	model_banghieu = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(10, 10, 10));
	nenbanghieu();
	chuP();
	chuH();
	chuO();
}
//========================TU KINH==============================
mat4 model_tukinh;
float tktk[] = { 0, 0, 0 };

void matsaukinh() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0, 0)) * scale(vec3(0.2, 0.4, 0.02));
	mat4 tudong = model_tukinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.51, 0.7, 1);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void matphaikinh() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.09, 0, 0.11)) * scale(vec3(0.02, 0.4, 0.2));
	mat4 tudong = model_tukinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.51, 0.7, 1);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void mattraikinh() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.09, 0, 0.11)) * scale(vec3(0.02, 0.4, 0.2));
	mat4 tudong = model_tukinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.51, 0.7, 1);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void matduoikinh() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, -0.19, 0.11)) * scale(vec3(0.16, 0.02, 0.2));
	mat4 tudong = model_tukinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1, 1, 0.86);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void mattrenkinh() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0.19, 0.11)) * scale(vec3(0.16, 0.02, 0.2));
	mat4 tudong = model_tukinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1, 1, 0.86);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void vachngankinh() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0.0, 0.11)) * scale(vec3(0.16, 0.02, 0.2));
	mat4 tudong = model_tukinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1, 1, 0.86);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void mattruoctrenkinh() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.1, 0.1, 0.22)) * rotate_y(tktk[0]) * translate(vec3(0.1, 0, 0)) * scale(vec3(0.2, 0.2, 0.02));
	mat4 tudong = model_tukinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.39, 0.48, 0.77);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void mattruocduoikinh() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.1, -0.1, 0.22)) * rotate_y(tktk[1]) * translate(vec3(0.1, 0, 0)) * scale(vec3(0.2, 0.2, 0.02));
	mat4 tudong = model_tukinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.49, 0.48, 0.77);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void tukinh(float x, float y, float z, int goc) {
	model_tukinh = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(5, 6, 5));
	matsaukinh();
	mattraikinh();
	matphaikinh();
	matduoikinh();
	vachngankinh();
	mattrenkinh();
	mattruoctrenkinh();
	mattruocduoikinh();
}





vec3	eye(0.0f, 0.0f, 20.0f),
at(0.0f, 0.0f, 0.0f),
up(0.0f, 1.0f, 0.0f);

float pitch = 0.0f;  // Xoay lên/xuống
float yaw = 0.0f;    // Xoay trái/phải

mat4 pitch_matrix = rotate_x(pitch);
mat4 yaw_matrix = rotate_y(yaw);
// Tạo ma trận quay tổng hợp
mat4 rotation_matrix = yaw_matrix * pitch_matrix;
vec3 up_direction = multiply_mat4_vec3(rotation_matrix, up);


void DisplayFunc(void)
{
	mat4 pitch_matrix = rotate_x(pitch);
	mat4 yaw_matrix = rotate_y(yaw);
	mat4 rotation_matrix = yaw_matrix * pitch_matrix;

	vec3 forward_direction = normalize(at - eye); // Hướng nhìn hiện tại
	vec3 rotated_forward = multiply_mat4_vec3(rotation_matrix, forward_direction);

	vec3 new_at = eye + rotated_forward; // Cập nhật điểm nhìn
	vec3 new_up = multiply_mat4_vec3(rotation_matrix, up); // Cập nhật hướng lên

	view_mat_cpp = lookat(eye, new_at, new_up);

	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	float
		znear = 0.1f,
		zfar = 100.0f,
		fov = 90.0f,
		aspect = (float)CurrentWidth / CurrentHeight;
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	//================ĐÔNG================
	phongchinh(0, 0, 0, 0);
	nhieu_quattran();
	nhieu_quatcay();
	tunuocngot(-13.9, -3.52, -12.0, -90);

	phong_wc(-3.9, -2.23, -19.9, 90);
	cua_wc(2., -3.2, -18.1, -90);
	chaurua(-4, -2, -24.5, -90);
	boncau(-7.25, -6.6, -22.5, 0);
	//================VÂN ANH================
	nhieu_hopdua();
	nhieu_thungrac();
	nhieu_nguoi();
	dongho(9.8, 3.0, 3.5, 90);
	nhieu_batdia();
	//=================DƯƠNG================

	ban_ghe();
	nhieu_dieuhoa();

	cuachinh(-7.7, -2.5, 25.1, 180);
	//=================HUYỀN================
	cuaso(-10, -2, 6.5, 90);
	cuaso(-10, -2, -2, 90);
	cuaso(-10, -2, 15, 90);
	bonruabat(8.8, -2.5, -23, 0);
	tubat(8.45, 1, 17.8, 90);
	//=================HÙNG================
	banbep(6.5, -3.8, 23, 0);
	bepgas(7.8, -3.7, 23.2, 180);
	xoong(6.3, -3.475, 23.05, 0);
	noipho(2.3, -6.35, 22.9, 180);
	tudong(9.75, -5.7, 17.0, -90);
	banghieu(0, 10.15, 25.1, 180);
	tukinh(5, -2.5, 23.5, 180);


	GLuint vertex_color_location = glGetUniformLocation(ProgramId, "vertex_color");
	glUniform4f(vertex_color_location, 0.0f, 0.0f, 1.0f, 1.0f);
	glUniform4f(vertex_color_location, 1.0f, 0.0f, 0.0f, 1.0f);

	
	glutSwapBuffers();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ------------------------------------------
void IdleFunc(void)
{
	// =================Quạt trần=============
	qtqt[0] += 10.0f;
	if (qtqt[0] > 360.0f) {
		qtqt[0] -= 360.0f;
	}

	qtqt[1] += 20.0f;
	if (qtqt[0] > 360.0f) {
		qtqt[0] -= 360.0f;
	}

	qtqt[2] += 90.0f;
	if (qtqt[0] > 360.0f) {
		qtqt[0] -= 360.0f;
	}

	// =================Quạt cây=============
	if (tupnang == 1) {
		qcqc[1] += tocdo_qc_tupnang;
		if (qcqc[1] > 60.0f || qcqc[1] < -60.0f) {
			tocdo_qc_tupnang = -tocdo_qc_tupnang;
		}
	}

	if (tocdo_qc_canh != 0) {
		qcqc[2] += 5.0f;
		if (qcqc[2] > 360.0f) {
			qcqc[2] -= 360.0f;
		}
		qcqc[3] += 90.0f;
		if (qcqc[3] > 360.0f) {
			qcqc[3] -= 360.0f;
		}
	}
	//------------------Đồng Hồ--------------------
	dhdh[0] -= 45.0f * 0.016; // Quay 30 độ mỗi giây
	if (dhdh[0] <= -360.0f) {
		dhdh[0] += 360.0f; // Đảm bảo góc quay không vượt quá 360 độ
	}
	glutPostRedisplay();
}
// ------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;


	case 'm':
		bcbc[0] -= 10;
		if (bcbc[0] < -90) bcbc[0] = -90;
		glutPostRedisplay();
		break;
	case 'n':
		bcbc[0] += 10;
		if (bcbc[0] > 0) bcbc[0] = 0;
		glutPostRedisplay();
		break;
	case 'M':
		bcbc[1] += 10;
		if (bcbc[1] > 50) bcbc[1] = 50;
		glutPostRedisplay();
		break;
	case 'N':
		bcbc[1] -= 10;
		if (bcbc[1] < 0) bcbc[1] = 0;
		glutPostRedisplay();
		break;
	case 'b':
		crcr[0] -= 30;
		nuoc = true;
		if (crcr[0] < -90) crcr[0] = -90;
		glutPostRedisplay();
		break;
	case 'v':
		crcr[0] += 30;
		if (crcr[0] > 0) {
			crcr[0] = 0;
			nuoc = false;
		}
		glutPostRedisplay();
		break;

	case 'z':
		tocdo_qt += 1;
		//check_qt = true;
		if (tocdo_qt > 3) {
			tocdo_qt = 0;
			//check_qt = false;
		}
		glutPostRedisplay();
		break;
	case 'c':
		nuocngot[0] -= 10;
		if (nuocngot[0] < -120) nuocngot[0] = -120;
		glutPostRedisplay();
		break;
	case 'x':
		nuocngot[0] += 10;
		if (nuocngot[0] > 0) nuocngot[0] = 0;
		glutPostRedisplay();
		break;
	case '.':
		cwc[1] += 15;
		if (cwc[1] > 90) cwc[1] = 90;
		glutPostRedisplay();
		break;
	case ',':
		cwc[1] -= 15;
		if (cwc[1] < 0) cwc[1] = 0;
		glutPostRedisplay();
		break;
	case '1':
		qcqc[0] -= 0.14;
		if (qcqc[0] < -1.26) qcqc[0] = -1.26;
		glutPostRedisplay();
		break;
	case '2':
		qcqc[0] += 0.14;
		if (qcqc[0] > 0) qcqc[0] = 0;
		glutPostRedisplay();
		break;
	case '3':
		tupnang += 1;
		if (tupnang > 1) tupnang = 0;
		glutPostRedisplay();
		break;
	case '4':
		tocdo_qc_canh += 1;
		if (tocdo_qc_canh > 2) tocdo_qc_canh = 0;
		glutPostRedisplay();
		break;
	case '5':
		qcqc[4] += 0.1;
		if (qcqc[4] > 2) qcqc[4] = 2;
		glutPostRedisplay();
		break;
	case '6':
		qcqc[4] -= 0.1;
		if (qcqc[4] < -2) qcqc[4] = -2;
		glutPostRedisplay();
		break;

	//============VÂN ANH==========
	case 'Q':
		thungrac[0] += 30;
		if (thungrac[0] > 90) thungrac[0] = 90;
		glutPostRedisplay();
		break;
	case 'W':
		thungrac[0] -= 30;
		if (thungrac[0] < 0) thungrac[0] = 0;
		glutPostRedisplay();
		break;
	case 'E':
		ngng[0] += 10;
		if (ngng[0] > 30) ngng[0] = 30;
		glutPostRedisplay();
		break;
	case 'R':
		ngng[0] -= 10;
		if (ngng[0] < -30) ngng[0] = -30;
		glutPostRedisplay();
		break;
	case 'T':
		ngng[1] += 5;
		if (ngng[1] > 30) ngng[1] = 30;
		glutPostRedisplay();
		break;
	case 'Y':
		ngng[1] -= 5;
		if (ngng[1] < -30) ngng[1] = -30;
		glutPostRedisplay();
		break;


	//============DƯƠNG==========
	case 'P':
		gg[0] -= 0.1;
		if (gg[0] < -0.2) gg[0] = -0.2;
		glutPostRedisplay();
		break;
	case 'O':
		gg[0] += 0.1;
		if (gg[0] > 1) gg[0] = 1;
		glutPostRedisplay();
		break;
	case 'I':
		Beta -= 5;
		if (Beta < -45) Beta = -45;
		glutPostRedisplay();
		break;
	case 'U':
		Beta += 5;
		if (Beta > 0) Beta = 0;
		glutPostRedisplay();
		break;
	case 'L':
		chch[0] += 30;
		if (chch[0] > 90) chch[0] = 90;
		glutPostRedisplay();
		break;
	case 'K':
		chch[0] -= 30;
		if (chch[0] < 0) chch[0] = 0;
		glutPostRedisplay();
		break;

	//=============HUYỀN============
	case 'Z':
		cst[0] -= 5;
		if (cst[0] < -150) cst[0] = -150;
		glutPostRedisplay();
		break;
	case 'X':
		csp[0] += 5;
		if (csp[0] > 150) csp[0] = 150;
		glutPostRedisplay();
		break;
	case 'C':
		cst[0] += 5;
		if (cst[0] > 0) cst[0] = 0;
		glutPostRedisplay();
		break;
	case 'V':
		csp[0] -= 5;
		if (csp[0] < 0) csp[0] = 0;
		glutPostRedisplay();
		break;
	case 'S':
		crb[0] += 30;
		if (crb[0] > 90) crb[0] = 90;
		glutPostRedisplay();
		break;
	case 'A':
		crb[0] -= 30;
		if (crb[0] < 0) crb[0] = 0;
		glutPostRedisplay();
		break;
	case '7':
		trb[0] += 10;
		if (trb[0] > 150) trb[0] = 150;
		glutPostRedisplay();
		break;
	case '8':
		trb[0] -= 10;
		if (trb[0] < 0) trb[0] = 0;
		glutPostRedisplay();
		break;

	//============HÙNG==========


	case 'F':
		tdtd[0] -= 10;
		if (tdtd[0] < -90) tdtd[0] = -90;
		glutPostRedisplay();
		break;
	case 'G':
		tdtd[0] += 10;
		if (tdtd[0] > 0) tdtd[0] = 0;
		glutPostRedisplay();
		break;
	case 'H':
		tdtd[1] -= 10;
		if (tdtd[1] < -90) tdtd[1] = -90;
		glutPostRedisplay();
		break;
	case 'J':
		tdtd[1] += 10;
		if (tdtd[1] > 0) tdtd[1] = 0;
		glutPostRedisplay();
		break;
	case '[':
		tktk[0] -= 10;
		if (tktk[0] < -180) tktk[0] = -180;
		glutPostRedisplay();
		break;
	case ']':
		tktk[0] += 10;
		if (tktk[0] > 0) tktk[0] = 0;
		glutPostRedisplay();
		break;
	case '=':
		tktk[1] -= 10;
		if (tktk[1] < -180) tktk[1] = -180;
		glutPostRedisplay();
		break;
	case '-':
		tktk[1] += 10;
		if (tktk[1] > 0) tktk[1] = 0;
		glutPostRedisplay();
		break;







	case 'w':  // Di chuyển camera về phía trước
		eye.z -= 0.5f;
		at.z -= 0.5f;
		break;
	case 's':  // Di chuyển camera về phía sau
		eye.z += 0.5f;
		at.z += 0.5f;
		break;
	case 'd':  // Di chuyển camera sang trái
		eye.x -= 0.5f;
		at.x -= 0.5f;
		break;
	case 'a':  // Di chuyển camera sang phải
		eye.x += 0.5f;
		at.x += 0.5f;
		break;
	case 'q':  // Di chuyển camera lên trên
		eye.y += 0.5f;
		at.y += 0.5f;
		break;
	case 'e':  // Di chuyển camera xuống dưới
		eye.y -= 0.5f;
		at.y -= 0.5f;
		break;

	case 'j':  // Xoay camera sang trái (yaw - tăng)
		yaw -= 2.0f; // Điều chỉnh giá trị này để thay đổi tốc độ quay
		break;
	case 'l':  // Xoay camera sang phải (yaw - giảm)
		yaw += 2.0f; // Điều chỉnh giá trị này để thay đổi tốc độ quay

		break;
	case 'i':  // Xoay camera lên (pitch - tăng)
		pitch += 2.0f; // Điều chỉnh giá trị này để thay đổi tốc độ quay
		break;
	case 'k':  // Xoay camera xuống (pitch - giảm)
		pitch -= 2.0f; // Điều chỉnh giá trị này để thay đổi tốc độ quay
		break;

	}
}
// ----------------------------------------

	// Xử lý phím đặc biệt
void SpecialFunc(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
		t[0] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_RIGHT:
		t[0] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_UP:
		t[1] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_DOWN:
		t[1] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_ALT_R:
		t[2] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_CTRL_R:
		t[2] += 0.05f;
		translated = true;
		break;
	}
}
// ------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Blinn");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();
	return 0;
}
