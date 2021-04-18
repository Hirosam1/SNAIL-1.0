#include "DataStructures/Matrix.hpp"

Matrix4::Matrix4(float identity){
    mat[0] = identity;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = identity;
    mat[6] = 0.0f;
    mat[7] = 0.0f;
    
    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = identity;
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = identity;
}

Matrix4::Matrix4(const Matrix4& mat_c){
    memcpy(mat,mat_c.mat, sizeof(GLfloat)*16);
}

const GLfloat* Matrix4::GetPtr() const{
    return &mat[0];
}

Matrix4 Matrix4::Multiply(float a){
    Matrix4 mat_c = Matrix4();

    mat_c.mat[0] = mat[0] * a;
    mat_c.mat[1] = mat[1] * a;
    mat_c.mat[2] = mat[2] * a;
    mat_c.mat[3] = mat[3] * a;

    mat_c.mat[4] = mat[4] * a;
    mat_c.mat[5] = mat[5] * a;
    mat_c.mat[6] = mat[6] * a;
    mat_c.mat[7] = mat[7] * a;
    
    mat_c.mat[8] = mat[8] * a;
    mat_c.mat[9] = mat[9] * a;
    mat_c.mat[10] = mat[10] * a;
    mat_c.mat[11] = mat[11] * a;

    mat_c.mat[12] = mat[12] * a;
    mat_c.mat[13] = mat[13] * a;
    mat_c.mat[14] = mat[14] * a;
    mat_c.mat[15] = mat[15] * a;

    return mat_c; 
}
 
Matrix4 Matrix4::operator*(float a){
    return Multiply(a);
}

Matrix4 Matrix4::Dot(const Matrix4& mat_cc) const{
    Matrix4 mat_c = Matrix4(1.0);
    //Column one
    mat_c.mat[0] = mat[0] * mat_cc.mat[0] + mat[4] * mat_cc.mat[1] + mat[8] * mat_cc.mat[2] + mat[12] * mat_cc.mat[3];
    mat_c.mat[4] = mat[0] * mat_cc.mat[4] + mat[4] * mat_cc.mat[5] + mat[8] * mat_cc.mat[6] + mat[12] * mat_cc.mat[7];
    mat_c.mat[8] = mat[0] * mat_cc.mat[8] + mat[4] * mat_cc.mat[9] + mat[8] * mat_cc.mat[10] + mat[12] * mat_cc.mat[11];
    mat_c.mat[12]=mat[0] * mat_cc.mat[12] + mat[4] * mat_cc.mat[13] + mat[8] * mat_cc.mat[14] + mat[12] * mat_cc.mat[15];
    //Column two
    mat_c.mat[1] = mat[1] * mat_cc.mat[0] + mat[5] * mat_cc.mat[1] + mat[9] * mat_cc.mat[2] + mat_cc.mat[13] * mat_cc.mat[3];
    mat_c.mat[5] = mat[1] * mat_cc.mat[4] + mat[5] * mat_cc.mat[5] + mat[9] * mat_cc.mat[6] + mat[13] * mat_cc.mat[7];
    mat_c.mat[9] = mat[1] * mat_cc.mat[8] + mat[5] * mat_cc.mat[9] + mat[9] * mat_cc.mat[10] + mat[13] * mat_cc.mat[11];
    mat_c.mat[13] = mat[1] * mat_cc.mat[12] + mat[5] * mat_cc.mat[13] + mat[9] * mat_cc.mat[14] + mat[13] * mat_cc.mat[15];
    //Column three
    mat_c.mat[2] = mat[2] * mat_cc.mat[0] + mat[6] * mat_cc.mat[1] + mat[10] * mat_cc.mat[2] + mat[14] * mat_cc.mat[3];
    mat_c.mat[6] = mat[2] * mat_cc.mat[4] + mat[6] * mat_cc.mat[5] + mat[10] * mat_cc.mat[6] + mat[14] * mat_cc.mat[7];
    mat_c.mat[10] = mat[2] * mat_cc.mat[8] + mat[6] * mat_cc.mat[9] + mat[10] * mat_cc.mat[10] + mat[14] * mat_cc.mat[11];
    mat_c.mat[14] = mat[2] * mat_cc.mat[12] + mat[6] * mat_cc.mat[13] + mat[10] * mat_cc.mat[14] + mat[14] * mat_cc.mat[15];
    //Column four
    mat_c.mat[3] = mat[3] * mat_cc.mat[0] + mat[7] * mat_cc.mat[1] + mat[11] * mat_cc.mat[2] + mat[15] * mat_cc.mat[3];
    mat_c.mat[7] = mat[3] * mat_cc.mat[4] + mat[7] * mat_cc.mat[5] + mat[11] * mat_cc.mat[6] + mat[15] * mat_cc.mat[7];
    mat_c.mat[11] = mat[3] * mat_cc.mat[8] + mat[7] * mat_cc.mat[9] + mat[11] * mat_cc.mat[10] + mat[15] * mat_cc.mat[11];
    mat_c.mat[15] = mat[3] * mat_cc.mat[12] + mat[7] * mat_cc.mat[13] + mat[11] * mat_cc.mat[14] + mat[15] * mat_cc.mat[15];
    
    return mat_c; 
}

Matrix4 Matrix4::operator*(const Matrix4& mat) const{
    return Dot(mat);
}

Vector4 Matrix4::Dot(const Vector4& vec) const{
    Vector4 vec_c = Vector4();
    vec_c.x = vec.x * mat[0] + vec.y * mat[4] + vec.z * mat[8] + vec.w * mat[12];
    vec_c.y = vec.x * mat[1] + vec.y * mat[5] + vec.z * mat[9] + vec.w * mat[13];
    vec_c.z = vec.x * mat[2] + vec.y * mat[6] + vec.z * mat[10] + vec.w * mat[14];
    vec_c.w = vec.x * mat[3] + vec.y * mat[7] + vec.z * mat[11] + vec.w * mat[15];

    return vec_c;
}

Vector4 Matrix4::Row(int n) const{
    return Vector4( mat[n*4],
                    mat[n*4 + 1],
                    mat[n*4 + 2],
                    mat[n*4 + 3]);
}

Vector4 Matrix4::Column(int n) const{
    return Vector4( mat[n],
                    mat[n + 4],
                    mat[n + 8],
                    mat[n + 12]);
}

Vector4 Matrix4::operator*(const Vector4& vec)const{
    return Dot(vec);
}

float* const Matrix4::operator[](unsigned int i) const{
    return (float* const) &mat[i*4];
}

std::ostream& operator<<(std::ostream& stream, const Matrix4& mat){

    const float* mat_f = (const float*) mat.mat;
    for(int i = 0; i < 4; i++){
        stream<<"| ";
        for(int j = 0; j < 4; j++){
         stream<< mat_f[i*4+j] <<" ";
        }
        stream<<" |\n";
    }
    return stream;
}