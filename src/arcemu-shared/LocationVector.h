/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2008-2011 <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _LOCATIONVECTOR_H
#define _LOCATIONVECTOR_H

///////////////////////////////////////////////////////////
// Location vector class (X, Y, Z, O)
//////////////////////////////////////////////////////////


class SERVER_DECL LocationVector
{
	public:
		// Constructors
		LocationVector(float X, float Y, float Z) : x(X), y(Y), z(Z), o(0) {}
		LocationVector(float X, float Y, float Z, float O) : x(X), y(Y), z(Z), o(O) {}
		LocationVector() : x(0), y(0), z(0), o(0) {}

		// (dx * dx + dy * dy + dz * dz)
		float DistanceSq(const LocationVector & comp)
		{
			float delta_x = comp.x - x;
			float delta_y = comp.y - y;
			float delta_z = comp.z - z;

			return (delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
		}

		float DistanceSq(const float & X, const float & Y, const float & Z)
		{
			float delta_x = X - x;
			float delta_y = Y - y;
			float delta_z = Z - z;

			return (delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
		}

		// sqrt(dx * dx + dy * dy + dz * dz)
		float Distance(const LocationVector & comp)
		{
			float delta_x = comp.x - x;
			float delta_y = comp.y - y;
			float delta_z = comp.z - z;

			return sqrtf(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
		}

		float Distance(const float & X, const float & Y, const float & Z)
		{
			float delta_x = X - x;
			float delta_y = Y - y;
			float delta_z = Z - z;

			return sqrtf(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
		}

		float Distance2DSq(const LocationVector & comp)
		{
			float delta_x = comp.x - x;
			float delta_y = comp.y - y;
			return (delta_x * delta_x + delta_y * delta_y);
		}

		float Distance2DSq(const float & X, const float & Y)
		{
			float delta_x = X - x;
			float delta_y = Y - y;
			return (delta_x * delta_x + delta_y * delta_y);
		}

		float Distance2D(LocationVector & comp)
		{
			float delta_x = comp.x - x;
			float delta_y = comp.y - y;
			return sqrtf(delta_x * delta_x + delta_y * delta_y);
		}

		float Distance2D(const float & X, const float & Y)
		{
			float delta_x = X - x;
			float delta_y = Y - y;
			return sqrtf(delta_x * delta_x + delta_y * delta_y);
		}

		// atan2(dx / dy)
		float CalcAngTo(const LocationVector & dest)
		{
			float dx = dest.x - x;
			float dy = dest.y - y;
			if(dy != 0.0f)
				return atan2(dy, dx);
			else
				return 0.0f;
		}

		float CalcAngFrom(const LocationVector & src)
		{
			float dx = x - src.x;
			float dy = y - src.y;
			if(dy != 0.0f)
				return atan2(dy, dx);
			else
				return 0.0f;
		}

		void ChangeCoords(float X, float Y, float Z, float O)
		{
			x = X;
			y = Y;
			z = Z;
			o = O;
		}

		void ChangeCoords(float X, float Y, float Z)
		{
			x = X;
			y = Y;
			z = Z;
		}
		float GetExactDist2d(float tx, float ty)
        { return sqrt(GetExactDist2dSq(tx, ty)); }

		float GetExactDist2dSq(float tx, float ty)
        { 
			float dx = x - tx; 
			float dy = y - ty; 
			return dx*dx + dy*dy; 
		}

		float GetAngle(float tx, float ty) const
		{
			float dx = tx - x;
			float dy = ty - y;

			float ang = atan2(dy, dx);
			ang = (ang >= 0) ? ang : 2 * 3.14159265358979323846f + ang;
			return ang;
		}
		float GetRelativeAngle(float tx, float ty) const { return GetAngle(tx, ty) - o; }

		float GetExactDistSq(float tx, float ty, float tz)
        { float dz = z - tz; return GetExactDist2dSq(tx, ty) + dz*dz; }

		// add/subtract/equality vectors
		LocationVector & operator += (const LocationVector & add)
		{
			x += add.x;
			y += add.y;
			z += add.z;
			o += add.o;
			return *this;
		}

		LocationVector & operator -= (const LocationVector & sub)
		{
			x -= sub.x;
			y -= sub.y;
			z -= sub.z;
			o -= sub.o;
			return *this;
		}

		LocationVector & operator = (const LocationVector & eq)
		{
			x = eq.x;
			y = eq.y;
			z = eq.z;
			o = eq.o;
			return *this;
		}

		bool operator == (const LocationVector & eq)
		{
			if(eq.x == x && eq.y == y && eq.z == z)
				return true;
			else
				return false;
		}

		float x;
		float y;
		float z;
		float o;
};

#endif
