#ifndef _S33ComplexEntity_H
#define _S33ComplexEntity_H

#include "S33Entity.h"

namespace Soshiant33
{
	//----------------------------------------------------
	//Joint Pettern
	/// تعریف مفصل
	struct S33JointPattern : public b2JointDef , public SPSerializable
	{
		//Parts Inistance name :
		std::string    body1Name;
		std::string    body2Name;

		//for Gear Joints
		std::string    joint1Name;
		std::string    joint2Name;
	protected:
		void serialize(SPArchive& archive);
	};
	//----------------------------------------------------
	//Complex Entity Pattern
	struct S33ComplexEntityPatternChilds : public SPSerializable
	{
		std::string patternName;
		S33EntityParameters  ep;
		S33EntityPattern::Types patternType;		
	protected:
		void serialize(SPArchive& archive);
	};
	class S33ComplexEntity;
	struct S33ComplexEntityPattern : public S33EntityPattern
	{
		friend class S33Library;
		friend class S33ComplexEntity;
		std::vector<S33JointPattern*>                   joints;
		std::vector<S33ComplexEntityPatternChilds*>  childs;

		S33ComplexEntityPattern(const char* name = 0,S33EntityPattern::Types type = S33EntityPattern::Type_ComplexEntityPattern);
		void Save(const char* name);
		void Load(const char* name);
	protected:
		void serializeBase_S33ComplexEntityPattern(SPArchive& archive);
		virtual void serialize(SPArchive& archive);
		~S33ComplexEntityPattern();
	};
	//----------------------------------------------------
	//Complex Entity
	/// موجودیت مرکب که از چند موجودیت تشکیل شده و بصورت سلسه مراتبی آنها را بروزرسانی می کند
	class S33ComplexEntity : public S33Entity
	{
		//friend class S33Sprite;
	protected:
		std::list<S33Entity*>::iterator    childsIterator;

		void renderChilds();
		void init(S33ComplexEntityPattern* complexEntityPattern);
	public:		
		std::list<S33Entity*>              childs;

		S33ComplexEntity(S33ComplexEntityPattern* complexEntityDef,S33EntityParameters* ep,S33ComplexEntity* parent);
		~S33ComplexEntity();

		S33Entity*   AddChild(S33EntityPattern* pattern,S33EntityParameters* ep);

		virtual void Update();
		virtual void Render();
		S33Entity* Pick(POINT* point);
		void SaveAsComplexEntityPattern(const char* name);
		void SortChildsByDepth();
		float GetDepth();
	};
}
#endif