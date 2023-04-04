#ifndef CLASSES_GAME_OBJECT_H_
#define CLASSES_GAME_OBJECT_H_

#include "../stringstream.h"

struct STypeTreeRoot;
struct STypeTree;

namespace nsu
{
	class GameObject : public CStringStream
	{
	public:
		GameObject();
		~GameObject();
		void SetLittleEndian(bool a_bLittleEndian);
		void SetTypeTreeRoot(const STypeTreeRoot* a_pTypeTreeRoot);
		void SetRefTypeTypeTree(const STypeTree* a_pRefTypeTypeTree);
		const string& GetName() const;
		bool ReadName();
	private:
		enum EReadNameStep
		{
			kReadNameStepBeforeRead,
			kReadNameStepReading,
			kReadNameStepAfterRead
		};
		bool readName();
		bool m_bLittleEndian;
		const STypeTreeRoot* m_pTypeTreeRoot;
		const STypeTree* m_pRefTypeTypeTree;
		string m_sName;
	};
}

#endif	// CLASSES_GAME_OBJECT_H_
