#pragma once
#include "stdafx.h"

class MyMatrix
{
public:
	double ** Content;
	int Height, Width;

	MyMatrix()
	{
		Height = Width = 0;
		Content = NULL;
	}
	MyMatrix(int h, int w, ...)
	{
		va_list ap;
		va_start(ap, w);

		Height = h;
		Width = w;
		this->Content = new double *[h];
		for (int i = 0; i < h; i++)
		{
			Content[i] = new double[w];
			for (int j = 0; j < w; j++)
			{
				Content[i][j] = va_arg(ap, double);
			}
		}
		va_end(ap);
	}
	MyMatrix(int h, int w, double all)
	{
		Height = h;
		Width = w;
		this->Content = new double *[h];
		for (int i = 0; i < h; i++)
		{
			Content[i] = new double[w];
			for (int j = 0; j < w; j++)
			{
				Content[i][j] = all;
			}
		}
	}
	MyMatrix(const MyMatrix & m)
	{
		Height = m.Height;
		Width = m.Width;
		this->Content = new double *[Height];
		for (int i = 0; i < Height; i++)
		{
			Content[i] = new double[Width];
			for (int j = 0; j < Width; j++)
			{
				Content[i][j] = m.Content[i][j];
			}
		}
	}
	~MyMatrix()
	{
		for (int i = 0; i < Height; i++)
			delete Content[i];
		delete Content;
	}

	MyMatrix& operator=(const MyMatrix & mat2)
	{
		if (this->Width != mat2.Width || this->Height != mat2.Height)
			return *this;

		for (int i = 0; i < this->Height; i++)
		{
			for (int j = 0; j < this->Width; j++)
			{
				this->Content[i][j] = mat2.Content[i][j];
			}
		}
		return *this;
	}
	MyMatrix& operator+=(const MyMatrix & mat2)
	{
		if (this->Width != mat2.Width || this->Height != mat2.Height)
			return *this;

		for (int i = 0; i < this->Height; i++)
		{
			for (int j = 0; j < this->Width; j++)
			{
				this->Content[i][j] += mat2.Content[i][j];
			}
		}
		return *this;
	}
	MyMatrix operator*(const MyMatrix & mat2) const
	{
		MyMatrix out(Height, mat2.Width, 0);
		if (Width != mat2.Height)
			return out;

		for (int i = 0; i < out.Height; i++)
		{
			for (int j = 0; j < out.Width; j++)
			{
				out.Content[i][j] = 0;
				for (int k = 0; k < Width; k++)
					out.Content[i][j] += Content[i][k] * mat2.Content[k][j];
			}
		}
		return out;
	}
	bool operator<(const MyMatrix & mat2) const
	{
		bool out = true;
		for (int i = 0; i < this->Height; i++)
		{
			for (int j = 0; j < this->Width; j++)
			{
				if (this->Content[i][j] >= mat2.Content[i][j])
					out = false;
			}
		}
		return out;
	}
	bool operator<(double d) const
	{
		bool out = true;
		for (int i = 0; i < this->Height; i++)
		{
			for (int j = 0; j < this->Width; j++)
			{
				if (abs(this->Content[i][j]) >= d)
					out = false;
			}
		}
		return out;
	}
	MyMatrix Transpose() const
	{
		MyMatrix m(Width, Height, 0);
		for (int i = 0; i < Width; i++)
		{
			for (int j = 0; j < Height; j++)
			{
				m.Content[i][j] = this->Content[j][i];
			}
		}
		return m;
	}
	MyMatrix Inverse() const
	{
		if (Height != Width) {
			return *this;
		}

		MyMatrix out = MyMatrix::Eye(Height);

		MyMatrix in = *this;


		//通过初等行变换将A变为上三角矩阵
		for (int i = 0; i < Height; i++) {
			//选取列主元
			int pivot = i;
			for (int j = i; j < Height; j++)
			{
				if (in.Content[j][i] > in.Content[pivot][i])
					pivot = j;
			}
			//交换主元行与当前行
			for (int k = 0; k < Width; k++)
			{
				double tmp = in.Content[i][k];
				in.Content[i][k] = in.Content[pivot][k];
				in.Content[pivot][k] = tmp;
				tmp = out.Content[i][k];
				out.Content[i][k] = out.Content[pivot][k];
				out.Content[pivot][k] = tmp;
			}

			//初等变换
			for (int j = i + 1; j < Height; j++) {
				double tmpRate = in.Content[j][i] / in.Content[i][i];
				for (int k = 0; k < Width; k++) {
					in.Content[j][k] -= in.Content[i][k] * tmpRate;
					out.Content[j][k] -= out.Content[i][k] * tmpRate;
				}
				in.Content[j][i] = 0;
			}
		}

		//使对角元素均为1
		for (int i = 0; i < Height; i++) {
			double tmp = in.Content[i][i];
			for (int j = 0; j < Width; j++) {
				in.Content[i][j] /= tmp;
				out.Content[i][j] /= tmp;
			}
		}
		//将已经变为上三角矩阵的A，变为单位矩阵
		for (int i = Height - 1; i >= 1; i--) {
			for (int j = i - 1; j >= 0; j--) {
				double tmp = in.Content[j][i];
				for (int k = 0; k < Width; k++) {
					in.Content[j][k] -= in.Content[i][k] * tmp;
					out.Content[j][k] -= out.Content[i][k] * tmp;
				}
			}
		}

		return out;

	}
	/*
	void display()
	{
		for (int i = 0; i < this->Height; i++)
		{
			for (int j = 0; j < this->Width; j++)
			{
				std::cout << Content[i][j] << ' ';
			}
			std::cout << std::endl;
		}
	}
	*/

	static MyMatrix LeastSquaresSolution(const MyMatrix & A, const MyMatrix & L)
	{
		MyMatrix X = (A.Transpose()*A).Inverse()*A.Transpose()*L;
		return X;
	}
	static MyMatrix Eye(int h)
	{
		MyMatrix out(h, h, 0);
		for (int i = 0; i < h; i++)
		{
			out.Content[i][i] = 1;
		}
		return out;
	}
};


