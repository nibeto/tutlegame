#ifndef _SEED_MANAGEMENT_H
#define _SEED_MANAGEMENT_H
#include"main.h"
#include"Scene2D.h"
class CSeedMAnagenet
{
public:
	CSeedMAnagenet();
	~CSeedMAnagenet();


	enum PlasticNumber
	{

		PlasticNumber_Eight = 0,
		PlasticNumber_Teen,
		PlasticNumber_Sixteen,
		PlasticNumber_MAX

	};
	enum Stringconversion
	{
		Stringconversion_Two = 0,
		Stringconversion_Eight,
		Stringconversion_Teen,
		Stringconversion_Sixteen,
		Stringconversion_MAX

	};
	enum FunctionTYPE
	{
		FunctionTYPE_Data = 0,
		FunctionTYPE_Finitestop,
		FunctionTYPE_Multiple,
		FunctionTYPE_Note,
		FunctionTYPE_Dontdoit,
		FunctionTYPE_Usually,
		FunctionTYPE_Partialsum,
		FunctionTYPE_MAX

	};
	enum ListMove
	{
		ListMove_NONE = 0,
		ListMove_ONE,
		ListMove_TWO,
		ListMove_MAX
	};
	void TheSeed(float f_Lessthan, float f_Morethan, float f_Plastic, PlasticNumber Prastic,float result);
	void TheSeedStringconversion(Stringconversion e_Stringconversion,float f_Plastic);
	void TheSeedDeffult(std::default_random_engine m_engine);
	void TheSeedDest(float f_Morethan, float f_Lessthan,float f_result);

	void TheSeedEightPlastic(float f_Plastic);
	void TheSeedteenPlastic(float f_Plastic);
	void TheSeedSixteenPlastic(float f_Plastic);

	void TheSeedTwoStringconversion(float f_Plastic);
	void TheSeedEightStringconversion(float f_Plastic);
	void TheSeedTenStringconversion(float f_Plastic);
	void TheSeedSixteenStringconversion(float f_Plastic);

	void TheSeedFunction(int nData, int nAdata, int nBdata, int nCdata, int nXDAta, int nNumData,int MAX_nDAta,D3DXVECTOR3 pos, FunctionTYPE nFunction);
	void TheSeedMove(float f_Move_X, float f_Move_Y, float f_rot,D3DXVECTOR3 move);
	void TheSeedMoveList(std::list<int> Xs, std::list<int> ys,ListMove listmove, int nMove);

	void TheSeedMoveListOne(std::list<int> Xs, std::list<int> ys,int nMove);
	void TheSeedMoveListTwo(std::list<int> Xs, std::list<int> ys,int nMove);
	void TheSeedMoveListThree(std::list<int> Xs, std::list<int> ys,int nMove);

	void TheSeedMoveListiterator(std::list<int>::iterator itr);
	void TheSeedMoveListiteratorTwo(std::list<int> lst);
	void TheSeedMoveListiteratorThree(std::list<int> lst);

	void TheSeedVector(void);
	void TheSeedVectorTwo(void);
	void TheSeedVectorThree(void);
	void TheSeedVectorFour(void);
	void TheSeedVectorFive(void);
	void TheSeedVectorSIX(void);
	void TheSeedVectorDelete(void);
	void TheSeedVectorDeleteTwo(void);
	void TheSeedVectorDeleteThree(void);
	void TheSeedVectorDeleteFour(void);

	//int getpass(istream stream);
	int Pass(void);
	int Func(int nData);
	void Function(int MAX_DATA);
	void FuncData(int nData);
	int  FuncnData(int nData);
	int Fibo(int nData);
	int FiboData(int nData,int MAX_nData);
	int VectorFunc(int nData ,int MAX_nData);
	long long Fibolong(int nData, vector<long long>& memo);
	bool fFunc();
	int Fibomain(int nData);
	int Sum(int nData,int MAX_nDAta,D3DXVECTOR3 pos);
	int Part(int nAdata, int nBdata, int nCdata,int nXDAta,int nNumData);
	float fSpped(float fSpped);

	void STDROTE(int argc, char const* argv[]);

	inline 	static  CSeedMAnagenet*GetSeed(void) { return m_Seedmnanagement; };
	inline static  float GetResult(void) { return m_fResult; };
	inline static  float GetRot(void) { return m_fRot; };
	inline static  float GetfMoveX(void) { return m_fMoveX; };
	inline static  float GetfMoveY(void) { return m_fMoveY; };
	inline static  float GetfMoveZ(void) { return m_fMoveZ; };
	inline static  D3DXVECTOR3 GetfMove(void) { return m_move; };
	inline static  float GetfSpeed(void) { return m_f_Speed; };

private:
	std::random_device m_seed_gen;
	std::default_random_engine m_engine;
	// -1.0以上1.0未満の値を等確率で発生させる
	std::uniform_real_distribution<> m_dist;
	static	CSeedMAnagenet *m_Seedmnanagement;
	float m_fMorethan, m_fLessthan;//以上//未満
	float m_fPlastic;//整形
	static float m_fResult;
	static float m_fRot;
	static float m_fMoveX;
	static float m_fMoveY;
	static float m_fMoveZ;
	static D3DXVECTOR3 m_move;
	static float m_f_Speed;
	mutable int mData;//リスト型「mutable」
	volatile int Vdata;//常にメモリにアクセスして変数を利用できる
	//throw int tData;
	};


#endif // !_SEED_MANAGEMENT_H
