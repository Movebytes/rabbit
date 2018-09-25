#pragma once
/**
 *  Copyright 2018 Movebytes Group
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
namespace aml {
// Transparency constants
#define OPAQUE (1.0f)
#define TRANSPARENT (0.0f)
// Basic colors
FColor White(1.0f, 1.0f, 1.0f, OPAQUE);
FColor Black(0.0f, 0.0f, 0.0f, OPAQUE);
FColor Cyan(0.0f, 1.0f, 1.0f, OPAQUE);
FColor Red(1.0f, 0.0f, 0.0f, OPAQUE);
FColor Green(0.0f, 1.0f, 0.0f, OPAQUE);
FColor Blue(0.0f, 0.0f, 1.0f, OPAQUE);
FColor Yellow(1.0f, 1.0f, 0.0f, OPAQUE);
FColor Transparent(1.0f, 0.0f, 1.0f, TRANSPARENT);
// Declaration of Material class
class Material
{
private:
	D3DMATERIAL9 m_data;
public:
	// Default constructor
	Material();
	// Accessors of Ambient part
	void SetAmbient(const FColor& color);
	const FColor GetAmbient() const;
	// Accessors of Diffuse part
	void SetDiffuse(const FColor& color);
	const FColor GetDiffuse() const;
	// Accessors of Specular part
	void SetSpecular(const FColor& color, const F32 fPower);
	void GetSpecular(FColor& OutColor, F32& OutPower) const;
	// Accessors of Emissive part
	void SetEmissive(const FColor& color);
	const FColor GetEmissive() const;
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
	m_data.Ambient = FColor(0.1f, 0.1f, 0.1f, OPAQUE);
	m_data.Specular = White;
	m_data.Emissive = Black;
}
// Accessors of Ambient part
inline void Material::SetAmbient(const FColor& color)
{
	m_data.Ambient = color;
}
inline const FColor Material::GetAmbient() const
{
	return m_data.Ambient;
}
// Accessors of Diffuse part
inline void Material::SetDiffuse(const FColor& color)
{
	m_data.Diffuse = color;
}
inline const FColor Material::GetDiffuse() const
{
	return m_data.Diffuse;
}
// Accessors of Specular part
inline void Material::SetSpecular(const FColor& color, const F32 fPower)
{
	m_data.Specular = color;
	m_data.Power = fPower;
}
inline void Material::GetSpecular(FColor& OutColor, F32& fOutPower) const
{
	OutColor = m_data.Specular;
	fOutPower = m_data.Power;
}
// Accessors of Emissive part
inline void Material::SetEmissive(const FColor& color)
{
	m_data.Emissive = color;
}
inline const FColor Material::GetEmissive() const
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
	return GetAlpha() != OPAQUE;
}
} // aml