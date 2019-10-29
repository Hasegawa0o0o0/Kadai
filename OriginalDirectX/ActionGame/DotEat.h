/**
* @file DotEat.h
* @brief �h�b�g�C�[�g�Ŏg�p����^
* @author �D�ˁ@�엲
* @date ���t�i2017.02.14�j
*/
#pragma once

#include "stdafx.h"
#include "Common3DType.h"

/*! @struct eDirection
@brief  ���� <��>
*/
typedef enum eDirection {
	eLeft,
	eRight,
	eUp,
	eDown,
	eNone
}eDirection;

/*! @struct FontInfo
@brief  �t�H���g <�ʒu>
*/
typedef struct FontInfo{
	char	ch;
	QuadrangleTexel	coord;
}FontInfo;

/*! @struct eChipType
@brief  �}�b�v�`�b�v <��>
*/
typedef enum eChipType
{
	eEmpty,
	eBlock,
	eDot,
	ePlayer,
	eGoal,
	eEnemy
}eChipType;

/*! @struct Size
@brief  �ʒu�E�T�C�Y <2D>
*/
typedef struct MapIndex {
	INT32 x;	//!< x�@/�@��
	INT32 y;	//!< y�@/�@�c
	
	BOOL operator== (MapIndex index_)
	{
		return (x == index_.x) && (y == index_.y);
	}

	BOOL operator!= (MapIndex index_)
	{
		return (x != index_.x) || (y != index_.y);
	}
}Size;