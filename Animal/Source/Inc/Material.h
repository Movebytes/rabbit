/**
 *  Copyright 2017 Movebytes Group
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#ifndef _AML_MATERIAL_H_
#define _AML_MATERIAL_H_
#include <d3dx9math.h>
#include "Types.h"
namespace aml {
// Define Color type
typedef D3DXCOLOR Color;
// Transparency constants
#define FILLED (1.0f)
#define TRANSPARENT (0.0f)
// Basic colors
Color White(1.0f, 1.0f, 1.0f, FILLED);
Color Black(0.0f, 0.0f, 0.0f, FILLED);
Color Cyan(0.0f, 1.0f, 1.0f, FILLED);
Color Red(1.0f, 0.0f, 0.0f, FILLED);
Color Green(0.0f, 1.0f, 0.0f, FILLED);
Color Blue(0.0f, 0.0f, 1.0f, FILLED);
Color Yellow(1.0f, 1.0f, 0.0f, FILLED);
Color Transparent(1.0f, 0.0f, 1.0f, TRANSPARENT);
// Declaration of Material class
class Material
{
private:
	D3DMATERIAL9 m_data;
public:
	// Default constructor
	Material();
	// Accessors of Ambient part
	void SetAmbient(const Color& color);
	const Color GetAmbient() const;
	// Accessors of Diffuse part
	void SetDiffuse(const Color& color);
	const Color GetDiffuse() const;
	// Accessors of Specular part
	void SetSpecular(const Color& color, const F32 fPower);
	void GetSpecular(Color& OutColor, F32& OutPower) const;
	// Accessors of Emissive part
	void SetEmissive(const Color& color);
	const Color GetEmissive() const;
	// Accessors of Alpha part
	void SetAlpha(const F32 fAlpha);
	F32 GetAlpha() const;
	// Check is alpha
	bool HasAlpha() const;
}; // Material
// Default constructor
inline Material::Material()
{
	ZeroMemory(&m_data, sizeof(D3DMATERIAL9));
	m_data.Diffuse = White;
	m_data.Ambient = Color(0.1f, 0.1f, 0.1f, FILLED);
	m_data.Specular = White;
	m_data.Emissive = Black;
}
// Accessors of Ambient part
inline void Material::SetAmbient(const Color& color)
{
	m_data.Ambient = color;
}
inline const Color Material::GetAmbient() const
{
	return m_data.Ambient;
}
// Accessors of Diffuse part
inline void Material::SetDiffuse(const Color& color)
{
	m_data.Diffuse = color;
}
inline const Color Material::GetDiffuse() const
{
	return m_data.Diffuse;
}
// Accessors of Specular part
inline void Material::SetSpecular(const Color& color, const F32 fPower)
{
	m_data.Specular = color;
	m_data.Power = fPower;
}
inline void Material::GetSpecular(Color& OutColor, F32& fOutPower) const
{
	OutColor = m_data.Specular;
	fOutPower = m_data.Power;
}
// Accessors of Emissive part
inline void Material::SetEmissive(const Color& color)
{
	m_data.Emissive = color;
}
inline const Color Material::GetEmissive() const
{
	return m_data.Emissive;
}
// Accessors of Alpha part
inline void Material::SetAlpha(const F32 fAlpha)
{
	m_data.Diffuse.a = fAlpha;
}
inline F32 Material::GetAlpha() const
{
	return m_data.Diffuse.a;
}
// Check is alpha
inline bool Material::HasAlpha() const
{
	return GetAlpha() != FILLED;
}
} // aml
#endif // _AML_MATERIAL_H_