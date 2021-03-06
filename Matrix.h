#ifndef __MATRIX_H__  
#define __MATRIX_H__  

#include <iostream>  
#include <fstream>  
#include <sstream>  
#include <vector>  
#include <string>  
#include <iomanip>  //用于设置输出格式 

using std::vector;  
using std::string;  
using std::cout;  
using std::cin;  
using std::istream;  
using std::ostream;  

// 新增的命名空间成员
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::cerr;
using std::endl;

// 任意类型矩阵类  
template <typename Object>
class MATRIX
{
public:
	explicit MATRIX() : array(0)
	{

	}

	MATRIX(int rows, int cols) :array(rows)
	{
		for (int i = 0; i < rows; ++i)
		{
			array[i].resize(cols);
		}
	}

	MATRIX(const MATRIX<Object>& m)
	{
		*this = m;
	}

	void resize(int rows, int cols);           // 改变当前矩阵大小  
	bool push_back(const vector<Object>& v);   // 在矩阵末尾添加一行数据  
	void swap_row(int row1, int row2);         // 交换两行的数据  

	int  rows() const
	{
		return array.size() ;
	}
	int  cols() const
	{
		return rows() ? (array[0].size()) : 0;
	}

	bool empty() const
	{
		return rows() == 0 || cols() == 0;
	}        // 是否为空  
	bool square() const
	{
		return (!(empty()) && rows() == cols());
	}  // 是否为方阵  


	const vector<Object>& operator[](int row) const
	{
		return array[row];
	} //[]操作符重载   
	vector<Object>& operator[](int row)
	{
		return array[row];
	}
	const Object& getAt(int row, int col)
	{
		return array.at(row).at(col);
	}

	void deleteRow(int rows);
	void deleteCol(int cols);
	bool findElem(Object elem, int& row, int& col);
	bool findElemFromRow(Object elem, int row, int& col);

protected:
	vector< vector<Object> > array;
};

// 
template <typename Object>
bool MATRIX<Object>::findElemFromRow(Object elem, int row, int& col)
{
	if (row<0 || row >= rows())
	{
		return false;
	}
	for (int i = 0; i<cols(); i++)
	{
		if (array[row][i] == elem)
		{
			col = i;
			return true;
		}
	}
	return false;
}
template <typename Object>
bool MATRIX<Object>::findElem(Object elem, int& row, int& col)
{
	row = 0;
	col = 0;
	for (int i = 0; i<rows(); i++)
	{
		for (int j = 0; j<cols(); j++)
		{
			if (array[i][j] == elem)
			{
				row = i;
				col = j;
				return true;
			}
		}
	}
	return false;
}
template <typename Object>
void MATRIX<Object>::deleteRow(int rows)
{
	int rs = this->rows();
	int cs = this->cols();
	if (rs <= 0 || cs <= 0 || rows >= rs)
	{
		return;
	}
	typename std::vector< vector<Object> >::iterator rowPtr = array.begin();
	for (int i = 0; i<rows; i++)
	{
		rowPtr++;
	}
	array.erase(rowPtr);
}
template <typename Object>
void MATRIX<Object>::deleteCol(int cols)
{
	int rs = this->rows();
	int cs = this->cols();

	if (rs <= 0 || cs <= 0 || cols >= cs)
	{
		return;
	}
	typename std::vector<Object>::iterator colPtr;
	for (int i = 0; i<rs; i++)
	{
		colPtr = array[i].begin();
		for (int j = 0; j<cols; j++)
		{
			colPtr++;
		}
		array[i].erase(colPtr);
	}

}

// 改变当前矩阵大小  
template <typename Object>
void MATRIX<Object>::resize(int rows, int cols)
{
	int rs = this->rows();
	int cs = this->cols();

	if (rows == rs && cols == cs)
	{
		return;
	}
	else if (rows == rs && cols != cs)
	{
		for (int i = 0; i < rows; ++i)
		{
			array[i].resize(cols);
		}
	}
	else if (rows != rs && cols == cs)
	{
		array.resize(rows);
		for (int i = rs; i < rows; ++i)
		{
			array[i].resize(cols);
		}
	}
	else
	{
		array.resize(rows);
		for (int i = 0; i < rows; ++i)
		{
			array[i].resize(cols);
		}
	}
}

// 在矩阵末尾添加一行  
template <typename Object>
bool MATRIX<Object>::push_back(const vector<Object>& v)
{
	if (rows() == 0 || cols() == (int)v.size())
	{
		array.push_back(v);
	}
	else
	{
		return false;
	}

	return true;
}


// 交换换两行  
template <typename Object>
void MATRIX<Object>::swap_row(int row1, int row2)
{
	if (row1 != row2 && row1 >= 0 &&
		row1 < rows() && row2 >= 0 && row2 < rows())
	{
		vector<Object>& v1 = array[row1];
		vector<Object>& v2 = array[row2];
		vector<Object> tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
}

// 矩阵转置  
template <typename Object>
const MATRIX<Object> trans(const MATRIX<Object>& m)
{
	MATRIX<Object> ret;
	if (m.empty()) return ret;

	int row = m.cols();
	int col = m.rows();
	ret.resize(row, col);

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			ret[i][j] = m[j][i];
		}
	}

	return ret;
}


//////////////////////////////////////////////////////////  
// double类型矩阵类，用于科学计算  
// 继承自MATRIX类  
// 实现常用操作符重载，并实现计算矩阵的行列式、逆以及LU分解  
class Matrix :public MATRIX<double>
{
	public:
		Matrix() :MATRIX<double>(){}
		Matrix(int r, int c) :MATRIX<double>(r, c){}
		Matrix(const Matrix& m){ *this = m; }

		const Matrix& operator+=(const Matrix& m);
		const Matrix& operator-=(const Matrix& m);
		const Matrix& operator*=(const Matrix& m);
		const Matrix& operator/=(const Matrix& m);

		//新增构造大小为r*c的零矩阵，不同
		const static Matrix zeros(int , int );

		//新增
		Matrix row(int i);
		Matrix col(int i);

		//新增，将数组f赋值给一个给定大小（num = r*c）的矩阵
		const bool elem(double *f, int num);

		//新增，点乘
		const static Matrix dot(const Matrix&, const Matrix&);

		// 新增，返回矩阵按对角线重复rep次后的结果
		const Matrix diag(int rep);

		// 新增，将两个矩阵按某种方式拼接
		// 0: 按行拼接  1: 按列拼接  2: 对角线拼接
		const Matrix joint(const Matrix&, int);

		// 未修改
		friend bool  operator==(const Matrix& lhs, const Matrix& rhs);        // 重载操作符==  
		friend bool  operator!=(const Matrix& lhs, const Matrix& rhs);        // 重载操作符!=  
		friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);  // 重载操作符+  
		friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);  // 重载操作符-
		friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);  // 重载操作符*
		friend Matrix operator/(const Matrix& lhs, const Matrix& rhs);  // 重载操作符/ 

		//新增运算符相关重载
		friend Matrix operator-(const Matrix& lhs);						 
		friend Matrix operator*(double lhs, const Matrix& rhs);
		friend Matrix operator*(const Matrix& lhs, double rhs);
		friend Matrix operator/(const Matrix& lhs, double rhs);

		//新增输出运算符重载
		friend ostream & operator<<(ostream &out, Matrix &);
		friend ofstream & operator<<(ofstream &out, Matrix &);

		// 未修改
		const static double det(const Matrix& m);                             // 计算行列式  
		const static double det(const Matrix& m, int start, int end);         // 计算子矩阵行列式 
		const static Matrix abs(const Matrix& m);                             // 计算所有元素的绝对值 
		const static double max(const Matrix& m);                             // 所有元素的最大值  
		const static double max(const Matrix& m, int& row, int& col);          // 所有元素中的最大值及其下标  
		const static double min(const Matrix& m);                             // 所有元素的最小值  
		const static double min(const Matrix& m, int& row, int& col);          // 所有元素的最小值及其下标 
		const static Matrix LU(const Matrix& m);							// 计算方阵的LU分解	
		const static Matrix submatrix(const Matrix& m, int rb, int re, int cb, int ce);  // 返回子矩阵

		//修改说明
		const double minPositive(const Matrix& m, int& row, int& col);          // 所有元素的最小值正值及其下标  

		Matrix t() const;                         // 返回转置矩阵  
		Matrix i() const;                         // 计算逆矩阵  

		// 输入输出相关
		const static Matrix readMatrix(istream& in = std::cin);               // 从指定输入流读入矩阵  
		const static Matrix readMatrix(string file);                          // 从文本文件读入矩阵  
		const static Matrix loadMatrix(string file);                          // 从二进制文件读取矩阵  
		void  static printMatrix(const Matrix& m, ostream& out = std::cout);  // 从指定输出流打印矩阵  
		void  static printMatrix(const Matrix& m, string file);                // 将矩阵输出到文本文件  
		void  static saveMatrix(const Matrix& m, string file);                 // 将矩阵保存为二进制文件  


		inline static double LxAbs(double d)
		{
			return (d >= 0) ? (d) : (-d);
		}

		inline static int max_idx(const Matrix& m, int k, int n)
		{
			int p = k;
			for (int i = k + 1; i < n; ++i)
			{
				if (LxAbs(m[p][k]) < LxAbs(m[i][k]))
				{
					p = i;
				}
			}
			return p;
		}

		inline	static bool isSignRev(const vector<double>& v)
		{
			int p = 0;
			int sum = 0;
			int n = (int)v.size();

			for (int i = 0; i < n; ++i)
			{
				p = (int)v[i];
				if (p >= 0)
				{
					sum += p + i;
				}
			}

			if (sum % 2 == 0) // 如果是偶数，说明不变号  
			{
				return false;
			}
			return true;
		}

		// 新增计算方阵的LU分解，按向量P，求逆矩阵速度更快
		const static void LUP(const Matrix& m, Matrix &L, Matrix &U, Matrix &P);
		const static Matrix LUP_Solve(Matrix L, Matrix U, Matrix P, Matrix b);
		const static Matrix LUP_inverse(Matrix A);
};


#endif  
