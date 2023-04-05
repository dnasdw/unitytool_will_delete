#ifndef CLASSES_TEXT_ASSET_H_
#define CLASSES_TEXT_ASSET_H_

#include "../stringstream.h"
#include "../typetree.h"

namespace nsu
{
	class TextAsset : public CStringStream
	{
	public:
		TextAsset();
		~TextAsset();
		void SetFileSize(n64 a_nFileSize);
		void SetLittleEndian(bool a_bLittleEndian);
		void SetTypeTreeRoot(const STypeTreeRoot* a_pTypeTreeRoot);
		void SetRefTypeTypeTree(const STypeTree* a_pRefTypeTypeTree);
		const string& GetScript() const;
		bool ReadScript();
	private:
		enum EReadScriptStep
		{
			kReadScriptStepBeforeRead,
			kReadScriptStepReading,
			kReadScriptStepAfterRead
		};
		bool readScriptCommon();
		bool readScript();
		static STypeTreeRoot s_TypeTreeRoot;
		static bool s_bInitRoot;
		n64 m_nFileSize;
		bool m_bLittleEndian;
		const STypeTreeRoot* m_pTypeTreeRoot;
		const STypeTree* m_pRefTypeTypeTree;
		string m_sScript;
	};
}

#endif	// CLASSES_TEXT_ASSET_H_
