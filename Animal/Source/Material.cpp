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
#include "Inc/AnimalStd.h"
#include "Inc/Material.h"
// Default constructor
aml::Material::Material()
{
	ZeroMemory(&m_data, sizeof(D3DMATERIAL9));
	m_data.Diffuse = White;
	m_data.Ambient = FColor(0.1f, 0.1f, 0.1f, OPAQUE);
	m_data.Specular = White;
	m_data.Emissive = Black;
}
// Accessors of Ambient part
void aml::Material::SetAmbient(const FColor& color)
{
	m_data.Ambient = color;
}
const FColor aml::Material::GetAmbient() const
{
	return m_data.Ambient;
}
// Accessors of Diffuse part
void aml::Material::SetDiffuse(const FColor& color)
{
	m_data.Diffuse = color;
}
const FColor aml::Material::GetDiffuse() const
{
	return m_data.Diffuse;
}
// Accessors of Specular part
void aml::Material::SetSpecular(const FColor& color, const F32 fPower)
{
	m_data.Specular = color;
	m_data.Power = fPower;
}
void aml::Material::GetSpecular(FColor& OutColor, F32& fOutPower) const
{
	OutColor = m_data.Specular;
	fOutPower = m_data.Power;
}
// Accessors of Emissive part
void aml::Material::SetEmissive(const FColor& color)
{
	m_data.Emissive = color;
}
const FColor aml::Material::GetEmissive() const
{
	return m_data.Emissive;
}
// Accessors of Alpha part
void aml::Material::SetAlpha(const F32 fAlpha)
{
	m_data.Diffuse.a = fAlpha;
}
F32 aml::Material::GetAlpha() const
{
	return m_data.Diffuse.a;
}
// Check is alpha
bool aml::Material::HasAlpha() const
{
	return GetAlpha() != OPAQUE;
}