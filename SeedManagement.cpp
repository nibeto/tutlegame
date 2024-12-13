//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//ヘッダーファイル
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
#include "SeedManagement.h"
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//静的メンバ変数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
CSeedMAnagenet *CSeedMAnagenet::m_Seedmnanagement = NULL;;//シードの静的メンバ変数
float CSeedMAnagenet::m_fResult = NULL;;//シードの静的メンバ変数
float CSeedMAnagenet::m_fMoveX = NULL;;//シードの静的メンバ変数
float CSeedMAnagenet::m_fMoveY = NULL;;//シードの静的メンバ変数
float CSeedMAnagenet::m_fMoveZ = NULL;;//シードの静的メンバ変数
float CSeedMAnagenet::m_fRot = NULL;;//シードの静的メンバ変数
D3DXVECTOR3 CSeedMAnagenet::m_move;//シードの静的メンバ変数
float CSeedMAnagenet::m_f_Speed = NULL;//シードの静的メンバ変数
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//コンストラクタ
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
CSeedMAnagenet::CSeedMAnagenet()
{
	try
	{

	}
	catch (const std::exception&)
	{

	m_Seedmnanagement = NULL;//シードの静的メンバ変数
	m_fLessthan = 0.0f;
	m_fMorethan = 0.0f;
	m_fPlastic = 0.0f;
	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//デストラクタ
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
CSeedMAnagenet::~CSeedMAnagenet()
{//空白

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seed全般管理
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeed(float f_Lessthan, float f_Morethan, float f_Plastic, PlasticNumber Prastic, float f_result)
{
	try
	{
		TheSeedDest(f_Lessthan, f_Morethan, f_result);//seedの等確立管理(以上から未満)
		switch (Prastic)
		{	//整数を整形
		case CSeedMAnagenet::PlasticNumber_Eight:
			TheSeedEightPlastic(f_Plastic);//seedを8進数に整形
			break;
		case CSeedMAnagenet::PlasticNumber_Teen:
			TheSeedteenPlastic(f_Plastic);//seedを10進数に整形
			break;
		case CSeedMAnagenet::PlasticNumber_Sixteen:
			TheSeedSixteenPlastic(f_Plastic);//seedを16進数に整形
			break;
		case CSeedMAnagenet::PlasticNumber_MAX:
			TheSeedEightPlastic(f_Plastic);//seedを8進数に整形
			TheSeedteenPlastic(f_Plastic);//seedを10進数に整形
			TheSeedSixteenPlastic(f_Plastic);//seedを16進数に整形
			break;
		default://それ以外の時

			break;//止める
		}

	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seed文字列管理
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedStringconversion(Stringconversion e_Stringconversion, float f_Plastic)
{
	try
	{
		switch (e_Stringconversion)
		{//整数の文字列変換
		case CSeedMAnagenet::Stringconversion_Two:
			TheSeedTwoStringconversion(f_Plastic);
			break;
		case CSeedMAnagenet::Stringconversion_Eight:
			TheSeedEightStringconversion(f_Plastic);
			break;
		case CSeedMAnagenet::Stringconversion_Teen:
			TheSeedTenStringconversion(f_Plastic);
			break;
		case CSeedMAnagenet::Stringconversion_Sixteen:
			TheSeedSixteenStringconversion(f_Plastic);
			break;
		case CSeedMAnagenet::Stringconversion_MAX:
			TheSeedTwoStringconversion(f_Plastic);
			TheSeedEightStringconversion(f_Plastic);
			TheSeedTenStringconversion(f_Plastic);
			TheSeedSixteenStringconversion(f_Plastic);
			break;
		default://それ以外
			break;//止める
		}
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedのデフォルトを管理
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedDeffult(std::default_random_engine m_engine)
{//デフォルトのランダムのデバイスエンジンをランダムデバイス(seedに代入)
	try
	{
		m_Seedmnanagement->m_seed_gen;//シード管理のseeddevice
		std::default_random_engine engine(m_Seedmnanagement->m_seed_gen());
		engine = m_engine;
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの等確立管理(以上から未満)
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedDest(float f_Morethan, float f_Lessthan, float f_result)
{// -1.0以上1.0未満の値を等確率で発生させる
	try
	{
		m_Seedmnanagement->m_seed_gen;//シード管理のseeddevice
		std::default_random_engine engine(m_Seedmnanagement->m_seed_gen());
		//m_Seedmnanagement->m_engine;//シード管理のseeddevice
		//TheSeedDeffult(m_Seedmnanagement->m_engine);
		std::uniform_real_distribution<> dist(f_Morethan, f_Lessthan);
		// 一様実数分布で乱数を生成する(キャスト)
		m_fResult = f_result;
		m_fResult = (float)dist(engine);
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの8進数に整形
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedEightPlastic(float f_Plastic)
{
	try
	{

		std::cout << std::oct << f_Plastic;//8進数に整形する
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの10進数に整形
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedteenPlastic(float f_Plastic)
{
	try
	{

		std::cout << std::dec << f_Plastic;//10進数に整形する
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの16進数に整形
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedSixteenPlastic(float f_Plastic)
{
	try
	{

		std::cout << std::hex << f_Plastic;//16進数に整形する
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの2進数への文字列変換
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedTwoStringconversion(float f_Plastic)
{
	try
	{

		std::stringstream ss;
		ss << std::bitset<8>((int)f_Plastic);//8&9
		std::string s = ss.str();
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの8進数の文字列変換
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedEightStringconversion(float f_Plastic)
{
	try
	{

		std::stringstream ss;
		ss << std::oct << f_Plastic;//9
		std::string s = ss.str();
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの10進数の文字列変換
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedTenStringconversion(float f_Plastic)
{
	try
	{

		std::stringstream ss;
		ss << std::dec << f_Plastic;//99
		std::string s = ss.str();
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの16進数の文字列変換
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedSixteenStringconversion(float f_Plastic)
{
	try
	{

		std::stringstream ss;
		ss << std::hex << f_Plastic;//16
		std::string s = ss.str();
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの再起関数全管理
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedFunction(int nData, int nAdata, int nBdata, int nCdata, int nXDAta, int nNumData, int MAX_nDAta, D3DXVECTOR3 pos, FunctionTYPE nFunction)
{
	try
	{
		switch (nFunction)
		{//再起関数の種類分け
		case CSeedMAnagenet::FunctionTYPE_Data://一般的な再起関数
			Func(nData);
			Function(nData);
			break;
		case CSeedMAnagenet::FunctionTYPE_Finitestop://有限停止性再起関数
			FuncData(nData);
			FuncnData(nData);
			break;
		case CSeedMAnagenet::FunctionTYPE_Multiple://複数再起関数
			Fibo(nData);
			FiboData(nData, MAX_nDAta);
			break;
		case CSeedMAnagenet::FunctionTYPE_Note://メモ化再起関数
			VectorFunc(nData, MAX_nDAta);
			break;
		case CSeedMAnagenet::FunctionTYPE_Dontdoit://再帰呼び出しを行わないで返す
			//Fibolong(nData, memo);
			Fibomain(nData);
			break;
		case CSeedMAnagenet::FunctionTYPE_Usually://通常の再起関数
			Sum(nData, MAX_nDAta, pos);
			break;
		case CSeedMAnagenet::FunctionTYPE_Partialsum://部分和再起関数
			Part(nAdata, nBdata, nCdata, nXDAta, nNumData);
			break;
		case CSeedMAnagenet::FunctionTYPE_MAX://再起関数の種類の最大
			Func(nData);
			Function(nData);
			FuncData(nData);
			FuncnData(nData);
			Fibo(nData);
			FiboData(nData, MAX_nDAta);
			VectorFunc(nData, MAX_nDAta);
			Fibomain(nData);
			Sum(nData, MAX_nDAta, pos);
			Part(nAdata, nBdata, nCdata, nXDAta, nNumData);
			break;
		default://それ以外
			break;//止める
		}
	}
	catch (const std::exception&)
	{

	}
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの移動関数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedMove(float f_Move_X, float f_Move_Y, float f_rot, D3DXVECTOR3 move)
{
	try
	{
		m_fMoveX = f_Move_X;
		m_fMoveY = f_Move_Y;
		m_fRot = f_rot;
		m_move = move;
		m_fMoveX = 0.0f, m_fMoveY = 0.0f;
	}
	catch (const std::exception&)
	{

	}
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//リスト移動管理関数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedMoveList(std::list<int> Xs, std::list<int> ys, ListMove listmove, int nMove)
{
	try
	{
		switch (listmove)
		{
		case CSeedMAnagenet::ListMove_NONE:
			TheSeedMoveListOne(Xs, ys, nMove);
			break;
		case CSeedMAnagenet::ListMove_ONE:
			TheSeedMoveListTwo(Xs, ys, nMove);
			break;
		case CSeedMAnagenet::ListMove_TWO:
			TheSeedMoveListThree(Xs, ys, nMove);
			break;
		case CSeedMAnagenet::ListMove_MAX:
			break;
		default:
			break;
		}
	}
	catch (const std::exception&)
	{

	}
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//全ての要素で移動するリストの移動関数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedMoveListOne(std::list<int> Xs, std::list<int> ys, int nMove)
{
	try
	{
		// ysの全ての要素をxsに移動する
		Xs = { nMove + 300, nMove + 400, nMove + 500 };
		ys = { nMove, nMove + 100, nMove + 200 };
		Xs.splice(Xs.begin(), std::move(ys));
	}
	catch (const std::exception&)
	{

	}
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//100だけ移動するリストの移動関数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedMoveListTwo(std::list<int> Xs, std::list<int> ys, int nMove)
{
	try
	{
		// ysのうち、100だけを移動する
		Xs = { nMove + 300, nMove + 400, nMove + 500 };
		ys = { nMove, nMove + 100, nMove + 200 };
		Xs.splice(Xs.begin(), std::move(ys), ys.begin());
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//100と200だけ移動するリストの移動関数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedMoveListThree(std::list<int> Xs, std::list<int> ys, int nMove)
{
	try
	{
		// ysのうち、100と200だけを移動する
		Xs = { nMove + 300, nMove + 400, nMove + 500 };
		ys = { nMove, nMove + 100, nMove + 200 };
		Xs.splice(Xs.begin(), std::move(ys), ys.begin(), std::next(ys.begin(), 2));
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedのイテレータ
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedMoveListiterator(std::list<int>::iterator itr)
{
	try
	{
		std::list<int> lst{ 1, 2, 3 };
		itr = lst.begin();// 最初の要素を指すイテレータ
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedのイテレータ2
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedMoveListiteratorTwo(std::list<int> lst)
{
	try
	{
		auto Itr = lst.begin();          //  最初の要素を指すイテレータ
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedのイテレータ3
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedMoveListiteratorThree(std::list<int> lst)
{
	try
	{
		auto Itr = lst.begin();          //  最初の要素を指すイテレータ
		std::cout << *Itr;               //  itr は最初の要素を指しているので 1 を表示
		*Itr = 9;                    // 最初の要素を 9 に変更
	}
	catch (const std::exception&){}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの動的配列
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedVector(void)
{
	try
	{
	int org_data[] = { 4, 6, 5 };      // 元データ
	std::vector<int> data(org_data, org_data + 3);     // 元データから動的配列を生成
	}
	catch (const std::exception&){}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの動的配列[2]
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedVectorTwo(void)
{
	try
	{
	std::vector<int> data{ 4, 6, 5 };
	}
	catch (const std::exception&){}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの動的配列[3]
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedVectorThree(void)
{
	try
	{
	int org_data[] = { 4, 6, 5 };      // 元データ
	std::vector<int> data(org_data, std::end(org_data));     // 元データから動的配列を生成
	}
	catch (const std::exception&){}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの動的配列[4]二次元配列
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedVectorFour(void)
{
	try
	{
	std::vector<std::vector<int>> vv{ { 1, 2, 3 },{ 4, 5, 6 } };
	}
	catch (const std::exception&){}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの動的配列[5]
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedVectorFive(void)
{
	try
	{
	std::vector<int> data{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
	for (int nData = 0; nData < 10; ++nData)
		std::cout << data.at(nData);      //  data の i 番目の要素を表示
	}
	catch (const std::exception&){}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの動的配列[6]
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedVectorSIX(void)
{
	try
	{
	const int SZ = 10;          // 要素数
	std::vector<int>v(SZ);        // 指定要素数で、vector を生成
	for (int i = 0; i < SZ; ++i)
		v.at(i) = i;             // 要素を 0, 1, 2, 3, ... 9 に設定
	}
	catch (const std::exception&){}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの削除
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedVectorDelete(void)
{
	try
	{
	std::vector<int> v{ 3, 1, 4, 1, 5 };
	v.pop_back();    //  末尾データ（この場合は 5）を削除
	}
	catch (const std::exception&){}
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの削除[2]
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedVectorDeleteTwo(void)
{
	try
	{
	std::vector<int> v{ 3, 1, 4, 1, 5 };
	int last = v.back();     // 末尾データを取り出しておく
	v.pop_back();            //  末尾データ（この場合は 5）を削除
	}
	catch (const std::exception&){}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの削除[3]
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedVectorDeleteThree(void)
{
	try
	{

		std::vector<int> v{ 3, 1, 9, 4 };
		v.erase(v.begin() + 2);       //  3番目の要素（9）を削除	}
	}
	catch (const std::exception&){}
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの削除[4]
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::TheSeedVectorDeleteFour(void)
{
	try
	{
	//if( !v.empty() ) {
	// v が空でなければ、なんらかの処理を行う
	//	}
	//for (int i = 0; i != v.size(); ++i) {      // 全要素に対するループ
	//}
	std::vector<int> v{ 3, 1, 4, 1, 5 };
	v.erase(v.begin() + 1, v.begin() + 3);       // 1, 4 を削除
	}
	catch (const std::exception&)
	{

	}
}

//int CSeedMAnagenet::getpass(istream stream)
//{
//
//	cout << '\a';
//	cout << "パスワードを入力";
//
//	// TODO: return ステートメントをここに挿入します
//}
int CSeedMAnagenet::Pass(void)
{
	try
	{
		char pW[80];
		do
		{
			//std::cin >> m_Seedmnanagement->getpass >> pW;
		} while (strcmp(pW, "passward"));
		cout << "ログオン完了\n";
	}
	catch (const std::exception&)
	{

	}

	return 0;
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの再起関数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
int CSeedMAnagenet::Func(int nData)
{
	try
	{
		if (nData == 0) return 0;//ベースケースに対する値

	}
	catch (const std::exception&)
	{

	}

	return nData + Func(nData - 1);//次の引数と答え
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの再起関数有限停止性
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::FuncData(int nData)
{
	if (nData == 0)return;

	try
	{
		std::cout << endl;

	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの再起関数有限停止性呼び出し
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
int CSeedMAnagenet::FuncnData(int nData)
{
	try
	{
		FuncData(nData);

	}
	catch (const std::exception&)
	{

	}

	return nData;
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの再起関数呼び出し複数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
int CSeedMAnagenet::Fibo(int nData)
{
	try
	{
		if (nData == 0)return 0;
		else if (nData == 1)return 1;
	}
	catch (const std::exception&)
	{

	}

	return Fibo(nData - 1) + Fibo(nData - 2);

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの再起関数呼び出し複数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
int CSeedMAnagenet::FiboData(int nData, int MAX_nData)
{
	try
	{
		for (nData = 0; nData < MAX_nData; nData++)//MAX_nData = 10
		{
			std::cout << nData << Fibo(nData) << endl;
		}
	}
	catch (const std::exception&)
	{

	}
	return 0;
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの動的計画法(メモ化再起関数)
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
int CSeedMAnagenet::VectorFunc(int nData, int MAX_nData)
{
	try
	{
		vector<long long> File(MAX_nData);//MAX_nData= 50
		File[0] = 0, File[1] = 1;
		for (nData = 2; nData < MAX_nData; nData++)
		{
			File[nData] = File[nData - 1] + File[nData - 2];
			std::cout << nData << File[nData] << endl;
		}
	}
	catch (const std::exception&)
	{

	}

	return nData;
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
 //
 //seedの再帰呼び出しを行わないで返す
 //
 //♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
long long CSeedMAnagenet::Fibolong(int nData, vector<long long>& memo)
{
	try
	{
		if (nData == 0)return 0;
		else if (nData == 1)return 1;

		if (memo[nData] != -1)return memo[nData];
	}
	catch (const std::exception&)
	{

	}

	return memo[nData] = Fibolong(nData - 1, memo) + Fibolong(nData - 2, memo);
}
//♠♠♠♠♠♠♠♠♠♠♠♠♠♠♠
//throw関数
//♠♠♠♠♠♠♠♠♠♠♠♠♠♠♠
bool CSeedMAnagenet::fFunc()
{
	struct X {};

	try {
		X* x = new X();
	}
	catch (std::bad_alloc& e) {
		// メモリ確保に失敗
		std::cout << e.what() << std::endl;
	}
	FILE *pf1 = NULL;
	FILE *pf2 = NULL;
	FILE *pf3 = NULL;

	bool bRet = false;

	//pf1= fopen()
	int negative = -1;
	int Small = 1;
	int large = INT_MAX;
	try {//投げられるべき3つの状況
		new int[negative];           // negative size
		new int[Small] {1, 2, 3};       // too many initializers
		new int[large][1000000];     // too large
	}
	catch (const std::bad_array_new_length &e) {
		std::cout << e.what() << '\n';
	}
	//例外処理//
	try
	{
		//課題1
		throw std::bad_alloc{};
		//課題2
		throw std::bad_array_new_length{};

		throw "";//例外処理
		cout << "";
	}
	catch (const char *str)
	{
		cout << str;
	}
	return bRet;
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
 //
 //seedの再帰呼び出しを行わないで返す
 //
 //♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
int CSeedMAnagenet::Fibomain(int nData)
{
	try
	{
		vector<long long> memo(50, -1);
		for (nData = 0; nData < 50; ++nData)
		{
			cout << nData << Fibolong(nData, memo) << endl;
		}
	}
	catch (const std::exception&)
	{

	}

	return nData;
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの通常の再起関数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
int CSeedMAnagenet::Sum(int nData, int MAX_nDAta, D3DXVECTOR3 pos)
{
	try
	{
		for (nData = 1; nData < MAX_nDAta; nData++)
		{
			pos.x += (float)nData;
			pos.y += (float)nData;
			pos.z += (float)nData;

		}
	}
	catch (const std::exception&)
	{

	}

	return nData;
}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの部分和問題
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
int CSeedMAnagenet::Part(int nAdata, int nBdata, int nCdata, int nXDAta, int nNumData)
{
	try
	{
		cin >> nAdata >> nBdata >> nCdata >> nXDAta;

		for (int aDAta = 0; aDAta <= nAdata; aDAta++)
		{
			for (int Bdata = 0; Bdata <= nBdata; Bdata++)
			{
				for (int cData = 0; cData <= nCdata; cData++)
				{
					if (500 * aDAta + 100 * Bdata + 50 * cData == nXDAta)
					{
						++nNumData;

					}
				}

			}

		}
		cout << nNumData << endl;
	}
	catch (const std::exception&)
	{

	}
	return nNumData;

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの速さの関数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
float CSeedMAnagenet::fSpped(float fSpped)
{
	try
	{
		m_f_Speed = fSpped;
		return m_f_Speed;
	}
	catch (const std::exception&)
	{

	}

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの回転の関数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::STDROTE(int argc, char const * argv[])
{
	try
	{
		vector<int> v{ 1,2,3,4,5 };
		auto dump = [](vector<int>& v) {
			for (auto i : v) { cout << i << " "; }
			cout << endl;
		};
		dump(v);

		//左に仮
		rotate(v.begin(), v.begin() + 1, v.end());
		dump(v);
		rotate(v.begin(), v.begin() + 1, v.end());
		dump(v);

		//右に仮
		rotate(v.rbegin(), v.rbegin() + 1, v.rend());
		dump(v);
		rotate(v.rbegin(), v.rbegin() + 1, v.rend());
		dump(v);

	}
	catch (const std::exception&)
	{

	}
		return;

}
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
//
//seedの最大数再起関数
//
//♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤♤
void CSeedMAnagenet::Function(int MAX_DATA)
{
	try
	{
		for (int nData = 0; nData < MAX_DATA; nData++)
		{
			std::cout << nData << Func(nData) << endl;
		}
	}
	catch (const std::exception&)
	{

	}

}