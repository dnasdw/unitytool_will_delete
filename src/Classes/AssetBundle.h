#ifndef CLASSES_ASSET_BUNDLE_H_
#define CLASSES_ASSET_BUNDLE_H_

#include "../stringstream.h"
#include "../typetree.h"

namespace nsu
{
	class AssetBundle : public CStringStream
	{
	public:
		AssetBundle();
		~AssetBundle();
		void SetAssetsVersion(n32 a_nAssetsVersion);
		void SetLittleEndian(bool a_bLittleEndian);
		void SetTypeTreeRoot(const STypeTreeRoot* a_pTypeTreeRoot);
		void SetRefTypeTypeTree(const STypeTree* a_pRefTypeTypeTree);
		const map<n32, map<n64, string>>& GetContainerFilePath() const;
		bool ReadContainer();
	private:
		enum ETravelContainerStep
		{
			kTravelContainerStepBeforeTravel,
			kTravelContainerStepTravelling,
			kTravelContainerStepAfterTravel
		};
		enum EContainerChildType
		{
			kContainerChildTypeNone,
			kContainerChildTypeArray,
			kContainerChildTypeArrayData,
			kContainerChildTypeArrayDataFirstSecond,
			kContainerChildTypeArrayDataSecondAsset,
			kContainerChildTypeArrayDataSecondAssetFileIdPathId
		};
		bool readContainerCommon();
		bool readContainer();
		bool mergeContainer(n32 a_nFileId, n64 a_nPathId, const string& a_sPath);
		static STypeTreeRoot s_TypeTreeRoot;
		static bool s_bInitRoot;
		n32 m_nAssetsVersion;
		bool m_bLittleEndian;
		const STypeTreeRoot* m_pTypeTreeRoot;
		const STypeTree* m_pRefTypeTypeTree;
		map<n32, map<n64, string>> m_mContainerFilePath;
	};
}

#endif	// CLASSES_ASSET_BUNDLE_H_
