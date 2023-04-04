#ifndef TYPECHECKER_H_
#define TYPECHECKER_H_

#include "stringstream.h"

struct STypeTreeRoot;
struct STypeTree;

class CTypeChecker : public CStringStream
{
public:
	CTypeChecker();
	~CTypeChecker();
	void SetLittleEndian(bool a_bLittleEndian);
	void SetTypeTreeRoot(const STypeTreeRoot* a_pTypeTreeRoot);
	void SetRefTypeTypeTree(const STypeTree* a_pRefTypeTypeTree);
	bool Travel();
private:
	bool m_bLittleEndian;
	const STypeTreeRoot* m_pTypeTreeRoot;
	const STypeTree* m_pRefTypeTypeTree;
};

#endif	// TYPECHECKER_H_
