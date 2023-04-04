#ifndef CLASSES_MONO_BEHAVIOUR_H_
#define CLASSES_MONO_BEHAVIOUR_H_

#include "../stringstream.h"
#include "../typetree.h"

namespace nsu
{
	class MonoBehaviour : public CStringStream
	{
	public:
		MonoBehaviour();
		~MonoBehaviour();
		void SetAssetsVersion(n32 a_nAssetsVersion);
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
		bool readNameCommon();
		bool readName();
		static STypeTreeRoot s_TypeTreeRoot;
		static bool s_bInitRoot;
		n32 m_nAssetsVersion;
		bool m_bLittleEndian;
		const STypeTreeRoot* m_pTypeTreeRoot;
		const STypeTree* m_pRefTypeTypeTree;
		string m_sName;
	};
}

#endif	// CLASSES_MONO_BEHAVIOUR_H_
