//
//  jmvector.cpp
//  jameo
//
//  Created by  Uwe Runtemund on 30.10.12.
//  Copyright (c) 2012 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

jm::Vector::Vector()
{
	m = 0;
	data = NULL;
}

jm::Vector::Vector(uint32 rows)
{
	m = rows;
	data = new double[rows];
	for(uint32 a = 0; a < m; a++)data[a] = 0.0;
}

jm::Vector::Vector(const Vector &another)
{
	m = another.m;
	if(m > 0)
	{
		data = new double[m];
		for(uint32 a = 0; a < m; a++)data[a] = another.data[a];
	}
	else data = NULL;
}

jm::Vector::~Vector()
{
	if(data != NULL)delete[] data;
	data = NULL;
	m = 0;
}

double jm::Vector::Abs() const
{
	double ret = 0;

	for(uint32 a = 0; a < m; a++)ret += data[a] * data[a];

	ret = std::sqrt(ret);

	return ret;
}

void jm::Vector::Normalize()
{
	double v = Abs();

	for(uint32 a = 0; a < m; a++)data[a] /= v;
}

void jm::Vector::Zeros()
{
	for(uint32 a = 0; a < m; a++)data[a] = 0.0;
}

void jm::Vector::Ones()
{
	for(uint32 a = 0; a < m; a++)data[a] = 1.0;
}

void jm::Vector::Print()
{
	std::cout << "[ ";
	for(uint32 a = 0; a < m; a++)std::cout << data[a] << ' ' ;
	std::cout << " ]";
}

double jm::Vector::DotProduct(const Vector &another) const
{
	double prod = 0.0;
	for(uint32 a = 0; a < m; a++)
	{
		prod += data[a] * another.data[a];
	}
	return prod;
}


jm::Vector& jm::Vector::operator=(const jm::Vector &another)
{
	if(this != &another)
	{
		if(data != NULL)delete[] data;
		m = another.m;
		if(m > 0)
		{
			data = new double[m];
			for(uint32 a = 0; a < m; a++)data[a] = another.data[a];
		}
		else data = NULL;
	}

	return *this;
}

const jm::Vector jm::operator+(const jm::Vector &v1, const jm::Vector &v2)
{
	if(v1.m != v2.m) throw "dimensions don't match";
	jm::Vector v = jm::Vector(v1.m);

	for(uint32 a = 0; a < v.m; a++)v.data[a] = v1.data[a] + v2.data[a];

	return v;
}

const jm::Vector jm::operator-(const jm::Vector &v1, const jm::Vector &v2)
{
	if(v1.m != v2.m) throw "dimensions don't match";

	if(v1.m != v2.m) throw "dimensions don't match";
	Vector v = Vector(v1.m);

	for(uint32 a = 0; a < v.m; a++)v.data[a] = v1.data[a] - v2.data[a];

	return v;
}

const jm::Vector jm::operator*(const double &d, const jm::Vector &v)
{
	jm::Vector r = jm::Vector(v.m);

	for(uint32 a = 0; a < v.m; a++)r.data[a] = d * v.data[a];

	return r;

}
