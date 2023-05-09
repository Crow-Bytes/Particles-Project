#include "Matrices.h"


namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols)
	{
		a.resize(rows);

		for (int i = 0; i < rows; i++)
		{
			a[i].resize(cols);

		}

	}

	///usage:  c = a + b;
	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if ((a.getRows() != b.getRows()) || (a.getCols() != b.getCols())) //if the rows or columns do not match, return ERROR
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), b.getCols()); //initializes each cell to 0

		for (int i = 0; i < a.getRows(); i++) // ROWS
		{
			for (int k = 0; k < a.getCols(); k++) // COLUMNS
			{
				c(i, k) = a(i, k) + b(i, k);
			}

		}

		return c;
	}


	///usage:  c = a * b;
	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), b.getCols());

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int k = 0; k < b.getCols(); k++)
			{
				for (int j = 0; j < a.getCols(); j++)
				{
					c(i, k) += a(i, j) * b(j, k);
				}
			}
		}

		return c;
	}


	///usage:  a == b
	bool operator==(const Matrix& a, const Matrix& b)
	{
		if ((a.getRows() != b.getRows()) || (a.getCols() != b.getCols())) //if the rows or columns do not match, return FALSE
		{
			return false;
		}
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (((a(i, j) - b(i, j)) < 0.001) || ((a(i, j) - b(i, j)) > -0.001))
				{
					return false;
				}
			}
		}

		return true;
	}

	///usage:  a != b
	bool operator!=(const Matrix& a, const Matrix& b)
	{
		if ((a.getRows() != b.getRows()) || (a.getCols() != b.getCols())) //if the rows or columns do not match, return true
		{
			return true;
		}
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (((a(i, j) - b(i, j)) > 0.001) || ((a(i, j) - b(i, j)) < -0.001))
				{
					return true;
				}
			}
		}

		return false;
	}

	///Output matrix.
	///Separate columns by ' ' and rows by '\n'
	ostream& operator<<(ostream& os, const Matrix& a)
	{

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int k = 0; k < a.getCols(); k++)
			{
				if (k != 0)
				{
					os << " ";
				}
				os << setw(10) << right << a(i, k);
			}
			os << '\n';
		}

		return os;
	}


	RotationMatrix::RotationMatrix(double theta) : Matrix(2,2) //SUCCESS
		//Format as:
		/*
		cos(theta)	-sin(theta)
		sin(theta)	 cos(theta)
		*/
	{
		
		a.at(0).at(0) = cos(theta); //Top Left
		a.at(1).at(1) = cos(theta); //Bottom Right

		a.at(0).at(1) = -sin(theta); //Top Right
		a.at(1).at(0) = sin(theta); //Bottom Left
	}

	ScalingMatrix::ScalingMatrix(double scale) : Matrix(2,2)
		//Format as:
		/*
		scale	0
		0	    scale
		*/
	{
		a.at(0).at(0) = scale; //Top Left
		a.at(1).at(1) = scale; //Bottom Right

		a.at(0).at(1) = 0; //Top Right
		a.at(1).at(0) = 0; //Bottom Left
	}

	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols) //SUCCESS
		//Format as:
			/*
			xShift	xShift	xShift	... nCols times
			yShift	yShift	yShift	... nCols times
			*/
	{
		int i = 0;
		while (i < nCols)
		{
			a.at(0).at(i) = xShift;
			a.at(1).at(i) = yShift;
			i++;
		}
	}
}
