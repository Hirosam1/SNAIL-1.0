#include "DataStructures/Vector.hpp"
#include "DataStructures/Matrix.hpp"

/*========================Vector 4====================================*/
#pragma region
void Vector4::SetValues(float x, float y, float z,float a){
    this->x = x;
    this->y = y;
    this->z = z;
    this->a = a;
}

//Add--------------------------------------------------------
Vector4 Vector4::Add(const Vector4& other)const{
    return Vector4(x + other.x, y + other.y, z + other.z, a + other.w);
}

Vector4 Vector4::Add(const float val)const{
    return Vector4(x + val, y + val, z + val, w + val);
}

Vector4 Vector4::operator+(const float val)const{
    return Add(val);
}

Vector4 Vector4::operator+(const Vector4& other)const{
    return Add(other);
}

//Subtract--------------------------------------------------
Vector4 Vector4::Subtract(const Vector4& other)const{
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4 Vector4::Subtract(const float val)const{
    return Vector4(x - val, y - val, z - val, w - val);
}

Vector4 Vector4::operator-(const float val)const{
    return Subtract(val);
}

Vector4 Vector4::operator-(const Vector4& other)const{
    return Subtract(other);
}

//Multiply--------------------------------------------------
Vector4 Vector4::Multiply(const Vector4& other)const{
    return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

Vector4 Vector4::Multiply(const float val )const{
    return Vector4(x * val, y * val, z * val, w * val);
}

Vector4 Vector4::Dot(const Matrix4& matrix) const{
    return matrix.Dot(*this);
}

Vector4 Vector4::operator*(const Vector4& other)const{
    return Multiply(other);
}

Vector4 Vector4::operator*(const float val)const{
    return Multiply(val);
}

Vector4 Vector4::operator*(const Matrix4& matrix) const{
    return Dot(matrix);
}

Vector4 Vector4::Divide(const float val) const {
    return Vector4(x / val, y / val, z / val, w/val);
}
Vector4 Vector4::operator/(const float val) const{
    return Divide(val);
}

//Matrix products ---------------------------------
float Vector4::Dot(const Vector4& other){
    return (x * other.x + y * other.y + z * other.z + w  *other.w);
}

//Printing
std::ostream& operator<<(std::ostream& stream, const Vector4& other){
    stream <<"(" <<other.x <<", " << other.y <<", " <<other.z<<", " << other.w <<")";
    return stream;
}

Vector4 operator*(float a, const Vector4& vec){
    return vec.Multiply(a);
}


Vector4 operator-(const Vector4& vec){
    return Vector4(-vec.x,-vec.y,-vec.z,-vec.w);
}

#pragma endregion

/*========================Vector 3====================================*/
#pragma region

void Vector3::SetValues(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
//Add--------------------------------------------------------
Vector3 Vector3::Add(const Vector3& other)const{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::Add(const float val)const{
    return Vector3(x + val, y + val, z + val);
}

Vector3 Vector3::operator+(const float val)const{
    return Add(val);
}

Vector3 Vector3::operator+(const Vector3& other)const{
    return Add(other);
}

void Vector3::operator+=(const Vector3& other){
    *this = this->Add(other);
}

//Subtract--------------------------------------------------
Vector3 Vector3::Subtract(const Vector3& other)const{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::Subtract(const float val)const{
    return Vector3(x - val, y - val, z - val);
}

Vector3 Vector3::operator-(const float val)const{
    return Subtract(val);
}

Vector3 Vector3::operator-(const Vector3& other)const{
    return Subtract(other);
}

void Vector3::operator-=(const Vector3& other){
    *this = this->Subtract(other);
}

//Multiply--------------------------------------------------
Vector3 Vector3::Multiply(const Vector3& other)const{
    return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::Multiply(const float val )const{
    return Vector3(x * val, y * val, z * val);
}

Vector3 Vector3::operator*(const Vector3& other)const{
    return Multiply(other);
}

Vector3 Vector3::operator*(const float val)const{
    return Multiply(val);
}

Vector3 Vector3::Divide(const float val) const {
    return Vector3(x / val, y / val, z / val);
}
Vector3 Vector3::operator/(const float val) const{
    return Divide(val);
}
//Matrix product
Vector3 Vector3::Cross(const Vector3& other) const{
    return Vector3( y * other.z - other.y  * z, 
                    z * other.x - other.z * x,
                    x *  other.y - other.x * y);
}

float Vector3::Dot(const Vector3& other) const{
    return (x * other.x + y * other.y + z * other.z);
}

//Printing
std::ostream& operator<<(std::ostream& stream, const Vector3& other){
    stream <<"(" <<other.x <<", " << other.y <<", " <<other.z<<")";
    return stream;
}

Vector3 operator*(float a, const Vector3& vec){
    return vec.Multiply(a);
}

Vector3 operator-(float a, const Vector3& vec){
    return vec.Subtract(a);
}

Vector3 operator-(const Vector3& vec){
    return Vector3(-vec.x,-vec.y,-vec.z);
}

#pragma endregion
/*========================Vector 2====================================*/
#pragma region
void Vector2::SetValues(float x, float y){
    this->x = x;
    this->y = y;
}

//Add--------------------------------------------------------
Vector2 Vector2::Add(const Vector2& other)const{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::Add(const float val)const{
    return Vector2(x + val, y + val);
}

Vector2 Vector2::operator+(const float val)const{
    return Add(val);
}

Vector2 Vector2::operator+(const Vector2& other)const{
    return Add(other);
}

//Subtract--------------------------------------------------
Vector2 Vector2::Subtract(const Vector2& other)const{
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::Subtract(const float val)const{
    return Vector2(x - val, y - val);
}

Vector2 Vector2::operator-(const float val)const{
    return Subtract(val);
}

Vector2 Vector2::operator-(const Vector2& other)const{
    return Subtract(other);
}

//Multiply--------------------------------------------------
Vector2 Vector2::Multiply(const Vector2& other)const{
    return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::Multiply(const float val )const{
    return Vector2(x * val, y * val);
}

Vector2 Vector2::operator*(const Vector2& other)const{
    return Multiply(other);
}

Vector2 Vector2::operator*(const float val)const{
    return Multiply(val);
}


Vector2 Vector2::Divide(const float val) const {
    return Vector2(x / val, y / val);
}
Vector2 Vector2::operator/(const float val) const{
    return Divide(val);
}

Vector2 Vector2::Rotate(float angle){
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    return Vector2(cos_a*x-sin_a*y,sin_a*x+cos_a*y);
}


//Printing
std::ostream& operator<<(std::ostream& stream, const Vector2& other){
    stream <<"(" <<other.x <<", " << other.y <<")";
    return stream;
}
//Global operations
Vector2 operator*(float a,const Vector2& vec){
    return vec.Multiply(a);
}
#pragma endregion

