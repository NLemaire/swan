/* DO NOT EDIT THIS FILE - it is machine generated */

#include "Schema2.h"
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


/******************** Free functions definitions ********************/

namespace schema2freefuncs
{
template<size_t x>
RealArray1D<x> sumR1(RealArray1D<x> a, RealArray1D<x> b)
{
	return a + b;
}
}

/******************** Options definition ********************/

void
Schema2::Options::jsonInit(const char* jsonContent)
{
	rapidjson::Document document;
	assert(!document.Parse(jsonContent).HasParseError());
	assert(document.IsObject());
	const rapidjson::Value::Object& o = document.GetObject();

	// outputPath
	assert(o.HasMember("outputPath"));
	const rapidjson::Value& valueof_outputPath = o["outputPath"];
	assert(valueof_outputPath.IsString());
	outputPath = valueof_outputPath.GetString();
	// outputPeriod
	assert(o.HasMember("outputPeriod"));
	const rapidjson::Value& valueof_outputPeriod = o["outputPeriod"];
	assert(valueof_outputPeriod.IsInt());
	outputPeriod = valueof_outputPeriod.GetInt();
	// Dload
	if (o.HasMember("Dload"))
	{
		const rapidjson::Value& valueof_Dload = o["Dload"];
		assert(valueof_Dload.IsBool());
		Dload = valueof_Dload.GetBool();
	}
	else
		Dload = true;
	// Dini
	if (o.HasMember("Dini"))
	{
		const rapidjson::Value& valueof_Dini = o["Dini"];
		assert(valueof_Dini.IsDouble());
		Dini = valueof_Dini.GetDouble();
	}
	else
		Dini = -1000.0;
	// Dup
	if (o.HasMember("Dup"))
	{
		const rapidjson::Value& valueof_Dup = o["Dup"];
		assert(valueof_Dup.IsDouble());
		Dup = valueof_Dup.GetDouble();
	}
	else
		Dup = -1000.0;
	// deltat
	if (o.HasMember("deltat"))
	{
		const rapidjson::Value& valueof_deltat = o["deltat"];
		assert(valueof_deltat.IsDouble());
		deltat = valueof_deltat.GetDouble();
	}
	else
		deltat = 0.5;
	// maxIter
	if (o.HasMember("maxIter"))
	{
		const rapidjson::Value& valueof_maxIter = o["maxIter"];
		assert(valueof_maxIter.IsInt());
		maxIter = valueof_maxIter.GetInt();
	}
	else
		maxIter = 5000000;
	// stopTime
	if (o.HasMember("stopTime"))
	{
		const rapidjson::Value& valueof_stopTime = o["stopTime"];
		assert(valueof_stopTime.IsDouble());
		stopTime = valueof_stopTime.GetDouble();
	}
	else
		stopTime = 20.0;
	// Loadwave
	if (o.HasMember("Loadwave"))
	{
		const rapidjson::Value& valueof_Loadwave = o["Loadwave"];
		assert(valueof_Loadwave.IsBool());
		Loadwave = valueof_Loadwave.GetBool();
	}
	else
		Loadwave = true;
	// Wavemode
	if (o.HasMember("Wavemode"))
	{
		const rapidjson::Value& valueof_Wavemode = o["Wavemode"];
		assert(valueof_Wavemode.IsInt());
		Wavemode = valueof_Wavemode.GetInt();
	}
	else
		Wavemode = 3;
	// LX
	if (o.HasMember("LX"))
	{
		const rapidjson::Value& valueof_LX = o["LX"];
		assert(valueof_LX.IsDouble());
		LX = valueof_LX.GetDouble();
	}
	else
		LX = 200.0;
	// X0
	if (o.HasMember("X0"))
	{
		const rapidjson::Value& valueof_X0 = o["X0"];
		assert(valueof_X0.IsDouble());
		X0 = valueof_X0.GetDouble();
	}
	else
		X0 = 50.0;
	// Y0
	if (o.HasMember("Y0"))
	{
		const rapidjson::Value& valueof_Y0 = o["Y0"];
		assert(valueof_Y0.IsDouble());
		Y0 = valueof_Y0.GetDouble();
	}
	else
		Y0 = 50.0;
	// Amp
	if (o.HasMember("Amp"))
	{
		const rapidjson::Value& valueof_Amp = o["Amp"];
		assert(valueof_Amp.IsDouble());
		Amp = valueof_Amp.GetDouble();
	}
	else
		Amp = 0.1;
	// Sigma
	if (o.HasMember("Sigma"))
	{
		const rapidjson::Value& valueof_Sigma = o["Sigma"];
		assert(valueof_Sigma.IsDouble());
		Sigma = valueof_Sigma.GetDouble();
	}
	else
		Sigma = 5000.0;
	// bathyLib
	if (o.HasMember("bathyLib"))
	{
		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		o["bathyLib"].Accept(writer);
		bathyLib.jsonInit(strbuf.GetString());
	}
}

/******************** Module definition ********************/

Schema2::Schema2(CartesianMesh2D* aMesh, Options& aOptions)
: mesh(aMesh)
, nbNodes(mesh->getNbNodes())
, nbNodesOfCell(CartesianMesh2D::MaxNbNodesOfCell)
, nbFaces(mesh->getNbFaces())
, nbInnerFaces(mesh->getNbInnerFaces())
, nbCells(mesh->getNbCells())
, nbInnerCells(mesh->getNbInnerCells())
, nbTopCells(mesh->getNbTopCells())
, nbBottomCells(mesh->getNbBottomCells())
, nbLeftCells(mesh->getNbLeftCells())
, nbRightCells(mesh->getNbRightCells())
, nbOuterCells(mesh->getNbOuterCells())
, options(aOptions)
, writer("Schema2", options.outputPath)
, lastDump(numeric_limits<int>::min())
, deltax(nbCells)
, deltay(nbCells)
, center(nbCells)
, X(nbNodes)
, Xc(nbInnerCells)
, U_n(nbFaces)
, U_nplus1(nbFaces)
, U_n0(nbFaces)
, Uini(nbFaces)
, Ucalc_n(nbFaces)
, Ucalc_nplus1(nbFaces)
, Ucalc_n0(nbFaces)
, Urn_n(nbFaces)
, Urn_nplus1(nbFaces)
, H_n(nbCells)
, H_nplus1(nbCells)
, H_n0(nbCells)
, Hini(nbCells)
, Hcalc_n(nbCells)
, Hcalc_nplus1(nbCells)
, Hcalc_n0(nbCells)
, Hru_n(nbCells)
, Hru_nplus1(nbCells)
, Hplot_n(nbCells)
, Hplot_nplus1(nbCells)
, Dijini(nbCells)
, Dij_n(nbCells)
, Dij_nplus1(nbCells)
, Dij_n0(nbCells)
, Dt_n(nbCells)
, Dt_nplus1(nbCells)
, Dt_n0(nbCells)
{
	// Copy node coordinates
	const auto& gNodes = mesh->getGeometry()->getNodes();
	for (size_t rNodes=0; rNodes<nbNodes; rNodes++)
	{
		X[rNodes][0] = gNodes[rNodes][0];
		X[rNodes][1] = gNodes[rNodes][1];
	}
}

Schema2::~Schema2()
{
}

/**
 * Job computeTn called @1.0 in executeTimeLoopN method.
 * In variables: deltat, t_n
 * Out variables: t_nplus1
 */
void Schema2::computeTn() noexcept
{
	t_nplus1 = t_n + options.deltat;
}

/**
 * Job iniCenter called @1.0 in simulate method.
 * In variables: X
 * Out variables: center
 */
void Schema2::iniCenter() noexcept
{
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		parallel_exec(nbInnerCells, [&](const size_t& jInnerCells)
		{
			const Id jId(innerCells[jInnerCells]);
			const size_t jCells(jId);
			RealArray1D<2> reduction0({0.0, 0.0});
			{
				const auto nodesOfCellJ(mesh->getNodesOfCell(jId));
				const size_t nbNodesOfCellJ(nodesOfCellJ.size());
				for (size_t rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					const Id rId(nodesOfCellJ[rNodesOfCellJ]);
					const size_t rNodes(rId);
					reduction0 = schema2freefuncs::sumR1(reduction0, X[rNodes]);
				}
			}
			center[jCells] = (0.25 * reduction0);
		});
	}
}

/**
 * Job initTime called @1.0 in simulate method.
 * In variables: 
 * Out variables: t_n0
 */
void Schema2::initTime() noexcept
{
	t_n0 = 0.0;
}

/**
 * Job initUini called @1.0 in simulate method.
 * In variables: 
 * Out variables: Uini
 */
void Schema2::initUini() noexcept
{
	{
		const auto innerFaces(mesh->getInnerFaces());
		const size_t nbInnerFaces(innerFaces.size());
		parallel_exec(nbInnerFaces, [&](const size_t& fInnerFaces)
		{
			const Id fId(innerFaces[fInnerFaces]);
			const size_t fFaces(fId);
			Uini[fFaces] = 0.0;
		});
	}
}

/**
 * Job initXc called @1.0 in simulate method.
 * In variables: 
 * Out variables: Xc
 */
void Schema2::initXc() noexcept
{
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		for (size_t icInnerCells=0; icInnerCells<nbInnerCells; icInnerCells++)
		{
			Xc[icInnerCells][0] = options.bathyLib.nextLon();
			Xc[icInnerCells][1] = options.bathyLib.nextLat();
		}
	}
}

/**
 * Job updateDij called @1.0 in executeTimeLoopN method.
 * In variables: Dij_n
 * Out variables: Dij_nplus1
 */
void Schema2::updateDij() noexcept
{
	parallel_exec(nbCells, [&](const size_t& jCells)
	{
		Dij_nplus1[jCells] = Dij_n[jCells];
	});
}

/**
 * Job updateHcalc called @1.0 in executeTimeLoopN method.
 * In variables: Dt_n, H_n, U_n, deltat, deltax, deltay
 * Out variables: Hcalc_nplus1
 */
void Schema2::updateHcalc() noexcept
{
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		parallel_exec(nbInnerCells, [&](const size_t& icInnerCells)
		{
			const Id icId(innerCells[icInnerCells]);
			const size_t icCells(icId);
			double TD1(0.0);
			double TD2(0.0);
			{
				const Id rfId(mesh->getRightFaceOfCell(icId));
				const size_t rfFaces(rfId);
				const Id rcId(mesh->getRightCell(icId));
				const size_t rcCells(rcId);
				if (U_n[rfFaces] <= 0) 
					TD1 = Dt_n[rcCells];
				else
					TD1 = Dt_n[icCells];
			}
			{
				const Id lfId(mesh->getLeftFaceOfCell(icId));
				const size_t lfFaces(lfId);
				const Id lcId(mesh->getLeftCell(icId));
				const size_t lcCells(lcId);
				if (U_n[lfFaces] <= 0) 
					TD2 = Dt_n[icCells];
				else
					TD2 = Dt_n[lcCells];
			}
			double TV1(0.0);
			double TV2(0.0);
			{
				const Id tfId(mesh->getTopFaceOfCell(icId));
				const size_t tfFaces(tfId);
				const Id tcId(mesh->getTopCell(icId));
				const size_t tcCells(tcId);
				if (U_n[tfFaces] <= 0) 
					TV1 = Dt_n[tcCells];
				else
					TV1 = Dt_n[icCells];
			}
			{
				const Id bfId(mesh->getBottomFaceOfCell(icId));
				const size_t bfFaces(bfId);
				const Id bcId(mesh->getBottomCell(icId));
				const size_t bcCells(bcId);
				if (U_n[bfFaces] <= 0) 
					TV2 = Dt_n[icCells];
				else
					TV2 = Dt_n[bcCells];
			}
			{
				const Id rfId(mesh->getRightFaceOfCell(icId));
				const size_t rfFaces(rfId);
				const Id lfId(mesh->getLeftFaceOfCell(icId));
				const size_t lfFaces(lfId);
				const Id tfId(mesh->getTopFaceOfCell(icId));
				const size_t tfFaces(tfId);
				const Id bfId(mesh->getBottomFaceOfCell(icId));
				const size_t bfFaces(bfId);
				Hcalc_nplus1[icCells] = H_n[icCells] - options.deltat / (deltax[icCells]) * (U_n[rfFaces] * TD1 - U_n[lfFaces] * TD2) - options.deltat / deltay[icCells] * (U_n[tfFaces] * TV1 - U_n[bfFaces] * TV2);
			}
		});
	}
}

/**
 * Job initDijini called @2.0 in simulate method.
 * In variables: Dini, Dload, Dup, LX, center
 * Out variables: Dijini
 */
void Schema2::initDijini() noexcept
{
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		for (size_t icInnerCells=0; icInnerCells<nbInnerCells; icInnerCells++)
		{
			const Id icId(innerCells[icInnerCells]);
			const size_t icCells(icId);
			if (options.Dload) 
				Dijini[icCells] = options.bathyLib.nextDepth();
			else
				Dijini[icCells] = options.Dini + center[icCells][0] * (options.Dup - options.Dini) / (options.LX);
		}
	}
}

/**
 * Job initHini called @2.0 in simulate method.
 * In variables: Amp, Loadwave, Sigma, Wavemode, X0, Y0, center
 * Out variables: Hini
 */
void Schema2::initHini() noexcept
{
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		for (size_t icInnerCells=0; icInnerCells<nbInnerCells; icInnerCells++)
		{
			const Id icId(innerCells[icInnerCells]);
			const size_t icCells(icId);
			if (options.Loadwave) 
				Hini[icCells] = options.bathyLib.nextWaveHeight();
			else
				if (options.Wavemode == 1) 
				if (center[icCells][0] < options.X0) 
				Hini[icCells] = options.Amp;
			else
				Hini[icCells] = 0.0;
			else
				if (options.Wavemode == 2) 
				Hini[icCells] = options.Amp * std::exp(-0.5 * (center[icCells][0] - options.X0) * (center[icCells][0] - options.X0) / (options.Sigma * options.Sigma)) * std::exp(-0.5 * (center[icCells][1] - options.Y0) * (center[icCells][1] - options.Y0) / (options.Sigma * options.Sigma));
			else
				if (options.Wavemode == 3) 
				Hini[icCells] = options.Amp * std::exp(-0.5 * (center[icCells][0] - options.X0) * (center[icCells][0] - options.X0) / (options.Sigma * options.Sigma));
		}
	}
}

/**
 * Job initU called @2.0 in simulate method.
 * In variables: Uini
 * Out variables: U_n0
 */
void Schema2::initU() noexcept
{
	{
		const auto topCells(mesh->getTopCells());
		const size_t nbTopCells(topCells.size());
		parallel_exec(nbTopCells, [&](const size_t& tcTopCells)
		{
			const Id tcId(topCells[tcTopCells]);
			const Id rfId(mesh->getRightFaceOfCell(tcId));
			const size_t rfFaces(rfId);
			const Id bcId(mesh->getBottomCell(tcId));
			const Id brfId(mesh->getRightFaceOfCell(bcId));
			const size_t brfFaces(brfId);
			U_n0[rfFaces] = Uini[brfFaces];
		});
	}
	{
		const auto bottomCells(mesh->getBottomCells());
		const size_t nbBottomCells(bottomCells.size());
		parallel_exec(nbBottomCells, [&](const size_t& bcBottomCells)
		{
			const Id bcId(bottomCells[bcBottomCells]);
			const Id rfId(mesh->getRightFaceOfCell(bcId));
			const size_t rfFaces(rfId);
			const Id tcId(mesh->getTopCell(bcId));
			const Id trfId(mesh->getRightFaceOfCell(tcId));
			const size_t trfFaces(trfId);
			U_n0[rfFaces] = Uini[trfFaces];
		});
	}
	{
		const auto leftCells(mesh->getLeftCells());
		const size_t nbLeftCells(leftCells.size());
		parallel_exec(nbLeftCells, [&](const size_t& lcLeftCells)
		{
			const Id lcId(leftCells[lcLeftCells]);
			const Id lfId(mesh->getLeftFaceOfCell(lcId));
			const size_t lfFaces(lfId);
			const Id rfId(mesh->getRightFaceOfCell(lcId));
			const size_t rfFaces(rfId);
			U_n0[lfFaces] = Uini[rfFaces];
		});
	}
	{
		const auto rightCells(mesh->getRightCells());
		const size_t nbRightCells(rightCells.size());
		parallel_exec(nbRightCells, [&](const size_t& rcRightCells)
		{
			const Id rcId(rightCells[rcRightCells]);
			const Id rfId(mesh->getRightFaceOfCell(rcId));
			const size_t rfFaces(rfId);
			const Id lfId(mesh->getLeftFaceOfCell(rcId));
			const size_t lfFaces(lfId);
			U_n0[rfFaces] = Uini[lfFaces];
		});
	}
}

/**
 * Job initdeltaxdeltay called @2.0 in simulate method.
 * In variables: DEG2M, DEG2M_DP, DEG2RAD, Xc, deltax_lon, deltay_lat
 * Out variables: deltax, deltay
 */
void Schema2::initdeltaxdeltay() noexcept
{
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		parallel_exec(nbInnerCells, [&](const size_t& icInnerCells)
		{
			const Id icId(innerCells[icInnerCells]);
			const size_t icCells(icId);
			deltax[icCells] = deltax_lon * DEG2M * std::cos(Xc[icInnerCells][1] * DEG2RAD);
			deltay[icCells] = deltay_lat * DEG2M_DP;
		});
	}
	{
		const auto outerCells(mesh->getOuterCells());
		const size_t nbOuterCells(outerCells.size());
		parallel_exec(nbOuterCells, [&](const size_t& ocOuterCells)
		{
			const Id ocId(outerCells[ocOuterCells]);
			const size_t ocCells(ocId);
			deltax[ocCells] = 3000.0;
			deltay[ocCells] = 3000.0;
		});
	}
}

/**
 * Job updateDtot called @2.0 in executeTimeLoopN method.
 * In variables: Dij_nplus1, Hcalc_nplus1
 * Out variables: Dt_nplus1
 */
void Schema2::updateDtot() noexcept
{
	parallel_exec(nbCells, [&](const size_t& jCells)
	{
		Dt_nplus1[jCells] = std::max(-Dij_nplus1[jCells] + Hcalc_nplus1[jCells], 0.0);
	});
}

/**
 * Job updateHru called @2.0 in executeTimeLoopN method.
 * In variables: Hcalc_nplus1
 * Out variables: Hru_nplus1
 */
void Schema2::updateHru() noexcept
{
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		parallel_exec(nbInnerCells, [&](const size_t& icInnerCells)
		{
			const Id icId(innerCells[icInnerCells]);
			const size_t icCells(icId);
			Hru_nplus1[icCells] = Hcalc_nplus1[icCells];
		});
	}
}

/**
 * Job initDij called @3.0 in simulate method.
 * In variables: Dijini
 * Out variables: Dij_n0
 */
void Schema2::initDij() noexcept
{
	{
		const auto topCells(mesh->getTopCells());
		const size_t nbTopCells(topCells.size());
		parallel_exec(nbTopCells, [&](const size_t& tcTopCells)
		{
			const Id tcId(topCells[tcTopCells]);
			const size_t tcCells(tcId);
			const Id bcId(mesh->getBottomCell(tcId));
			const size_t bcCells(bcId);
			Dij_n0[tcCells] = Dijini[bcCells];
		});
	}
	{
		const auto bottomCells(mesh->getBottomCells());
		const size_t nbBottomCells(bottomCells.size());
		parallel_exec(nbBottomCells, [&](const size_t& bcBottomCells)
		{
			const Id bcId(bottomCells[bcBottomCells]);
			const size_t bcCells(bcId);
			const Id tcId(mesh->getTopCell(bcId));
			const size_t tcCells(tcId);
			Dij_n0[bcCells] = Dijini[tcCells];
		});
	}
	{
		const auto leftCells(mesh->getLeftCells());
		const size_t nbLeftCells(leftCells.size());
		parallel_exec(nbLeftCells, [&](const size_t& lcLeftCells)
		{
			const Id lcId(leftCells[lcLeftCells]);
			const size_t lcCells(lcId);
			const Id rcId(mesh->getRightCell(lcId));
			const size_t rcCells(rcId);
			Dij_n0[lcCells] = Dijini[rcCells];
		});
	}
	{
		const auto rightCells(mesh->getRightCells());
		const size_t nbRightCells(rightCells.size());
		parallel_exec(nbRightCells, [&](const size_t& rcRightCells)
		{
			const Id rcId(rightCells[rcRightCells]);
			const size_t rcCells(rcId);
			const Id lcId(mesh->getLeftCell(rcId));
			const size_t lcCells(lcId);
			Dij_n0[rcCells] = Dijini[lcCells];
		});
	}
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		parallel_exec(nbInnerCells, [&](const size_t& icInnerCells)
		{
			const Id icId(innerCells[icInnerCells]);
			const size_t icCells(icId);
			Dij_n0[icCells] = Dijini[icCells];
		});
	}
}

/**
 * Job initH called @3.0 in simulate method.
 * In variables: Hini
 * Out variables: H_n0
 */
void Schema2::initH() noexcept
{
	{
		const auto topCells(mesh->getTopCells());
		const size_t nbTopCells(topCells.size());
		parallel_exec(nbTopCells, [&](const size_t& tTopCells)
		{
			const Id tId(topCells[tTopCells]);
			const size_t tCells(tId);
			const Id btId(mesh->getBottomCell(tId));
			const size_t btCells(btId);
			H_n0[tCells] = Hini[btCells];
		});
	}
	{
		const auto bottomCells(mesh->getBottomCells());
		const size_t nbBottomCells(bottomCells.size());
		parallel_exec(nbBottomCells, [&](const size_t& bBottomCells)
		{
			const Id bId(bottomCells[bBottomCells]);
			const size_t bCells(bId);
			const Id tbId(mesh->getTopCell(bId));
			const size_t tbCells(tbId);
			H_n0[bCells] = Hini[tbCells];
		});
	}
	{
		const auto leftCells(mesh->getLeftCells());
		const size_t nbLeftCells(leftCells.size());
		parallel_exec(nbLeftCells, [&](const size_t& lLeftCells)
		{
			const Id lId(leftCells[lLeftCells]);
			const size_t lCells(lId);
			const Id rlId(mesh->getRightCell(lId));
			const size_t rlCells(rlId);
			H_n0[lCells] = Hini[rlCells];
		});
	}
	{
		const auto rightCells(mesh->getRightCells());
		const size_t nbRightCells(rightCells.size());
		parallel_exec(nbRightCells, [&](const size_t& rRightCells)
		{
			const Id rId(rightCells[rRightCells]);
			const size_t rCells(rId);
			const Id lrId(mesh->getLeftCell(rId));
			const size_t lrCells(lrId);
			H_n0[rCells] = Hini[lrCells];
		});
	}
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		parallel_exec(nbInnerCells, [&](const size_t& icInnerCells)
		{
			const Id icId(innerCells[icInnerCells]);
			const size_t icCells(icId);
			H_n0[icCells] = Hini[icCells];
		});
	}
}

/**
 * Job initUcalc called @3.0 in simulate method.
 * In variables: U_n0
 * Out variables: Ucalc_n0
 */
void Schema2::initUcalc() noexcept
{
	parallel_exec(nbFaces, [&](const size_t& jFaces)
	{
		Ucalc_n0[jFaces] = U_n0[jFaces];
	});
}

/**
 * Job updateHinner called @3.0 in executeTimeLoopN method.
 * In variables: Hru_nplus1
 * Out variables: H_nplus1
 */
void Schema2::updateHinner() noexcept
{
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		parallel_exec(nbInnerCells, [&](const size_t& icInnerCells)
		{
			const Id icId(innerCells[icInnerCells]);
			const size_t icCells(icId);
			H_nplus1[icCells] = Hru_nplus1[icCells];
		});
	}
}

/**
 * Job updateHouter called @3.0 in executeTimeLoopN method.
 * In variables: Hru_nplus1
 * Out variables: H_nplus1
 */
void Schema2::updateHouter() noexcept
{
	{
		const auto topCells(mesh->getTopCells());
		const size_t nbTopCells(topCells.size());
		parallel_exec(nbTopCells, [&](const size_t& tcTopCells)
		{
			const Id tcId(topCells[tcTopCells]);
			const size_t tcCells(tcId);
			const Id bcId(mesh->getBottomCell(tcId));
			const size_t bcCells(bcId);
			H_nplus1[tcCells] = Hru_nplus1[bcCells];
		});
	}
	{
		const auto bottomCells(mesh->getBottomCells());
		const size_t nbBottomCells(bottomCells.size());
		parallel_exec(nbBottomCells, [&](const size_t& bcBottomCells)
		{
			const Id bcId(bottomCells[bcBottomCells]);
			const size_t bcCells(bcId);
			const Id tcId(mesh->getTopCell(bcId));
			const size_t tcCells(tcId);
			H_nplus1[bcCells] = Hru_nplus1[tcCells];
		});
	}
	{
		const auto leftCells(mesh->getLeftCells());
		const size_t nbLeftCells(leftCells.size());
		parallel_exec(nbLeftCells, [&](const size_t& lcLeftCells)
		{
			const Id lcId(leftCells[lcLeftCells]);
			const size_t lcCells(lcId);
			const Id rcId(mesh->getRightCell(lcId));
			const size_t rcCells(rcId);
			H_nplus1[lcCells] = Hru_nplus1[rcCells];
		});
	}
	{
		const auto rightCells(mesh->getRightCells());
		const size_t nbRightCells(rightCells.size());
		parallel_exec(nbRightCells, [&](const size_t& rcRightCells)
		{
			const Id rcId(rightCells[rcRightCells]);
			const size_t rcCells(rcId);
			const Id lcId(mesh->getLeftCell(rcId));
			const size_t lcCells(lcId);
			H_nplus1[rcCells] = Hru_nplus1[lcCells];
		});
	}
}

/**
 * Job updateHplot called @3.0 in executeTimeLoopN method.
 * In variables: Dij_nplus1, Hru_nplus1
 * Out variables: Hplot_nplus1
 */
void Schema2::updateHplot() noexcept
{
	parallel_exec(nbCells, [&](const size_t& jCells)
	{
		if (Dij_nplus1[jCells] < 0) 
			Hplot_nplus1[jCells] = Hru_nplus1[jCells];
		else
			Hplot_nplus1[jCells] = Dij_nplus1[jCells];
	});
}

/**
 * Job iniDt called @4.0 in simulate method.
 * In variables: Dij_n0, H_n0
 * Out variables: Dt_n0
 */
void Schema2::iniDt() noexcept
{
	parallel_exec(nbCells, [&](const size_t& jCells)
	{
		Dt_n0[jCells] = std::max(H_n0[jCells], H_n0[jCells] - Dij_n0[jCells]);
	});
}

/**
 * Job initHcalc called @4.0 in simulate method.
 * In variables: H_n0
 * Out variables: Hcalc_n0
 */
void Schema2::initHcalc() noexcept
{
	parallel_exec(nbCells, [&](const size_t& jCells)
	{
		Hcalc_n0[jCells] = H_n0[jCells];
	});
}

/**
 * Job updateUcalc called @4.0 in executeTimeLoopN method.
 * In variables: H_nplus1, U_n, deltat, deltax, deltay, g
 * Out variables: Ucalc_nplus1
 */
void Schema2::updateUcalc() noexcept
{
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		parallel_exec(nbInnerCells, [&](const size_t& icInnerCells)
		{
			const Id icId(innerCells[icInnerCells]);
			const size_t icCells(icId);
			const Id rfcId(mesh->getRightFaceOfCell(icId));
			const size_t rfcFaces(rfcId);
			const Id tfcId(mesh->getTopFaceOfCell(icId));
			const size_t tfcFaces(tfcId);
			double TU1(0.0);
			double TV1(0.0);
			double V1(0.0);
			{
				const Id bfcId(mesh->getBottomFaceOfCell(icId));
				const size_t bfcFaces(bfcId);
				const Id icpId(mesh->getRightCell(icId));
				const Id tfcpId(mesh->getTopFaceOfCell(icpId));
				const size_t tfcpFaces(tfcpId);
				const Id bfcpId(mesh->getBottomFaceOfCell(icpId));
				const size_t bfcpFaces(bfcpId);
				V1 = (U_n[tfcFaces] + U_n[bfcFaces] + U_n[tfcpFaces] + U_n[bfcpFaces]) / 4;
			}
			if (V1 <= 0) 
			{
				const Id ictId(mesh->getTopCell(icId));
				const Id rfctId(mesh->getRightFaceOfCell(ictId));
				const size_t rfctFaces(rfctId);
				TV1 = U_n[rfctFaces] - U_n[rfcFaces];
			}
			else
			{
				const Id icbId(mesh->getBottomCell(icId));
				const Id rfcbId(mesh->getRightFaceOfCell(icbId));
				const size_t rfcbFaces(rfcbId);
				TV1 = U_n[rfcFaces] - U_n[rfcbFaces];
			}
			if (U_n[rfcFaces] <= 0) 
			{
				const Id icpId(mesh->getRightCell(icId));
				const Id rfcpId(mesh->getRightFaceOfCell(icpId));
				const size_t rfcpFaces(rfcpId);
				const Id lfcpId(mesh->getLeftFaceOfCell(icpId));
				const size_t lfcpFaces(lfcpId);
				TU1 = U_n[rfcpFaces] - U_n[lfcpFaces];
			}
			else
			{
				const Id lfcId(mesh->getLeftFaceOfCell(icId));
				const size_t lfcFaces(lfcId);
				TU1 = U_n[rfcFaces] - U_n[lfcFaces];
			}
			{
				const Id icpId(mesh->getRightCell(icId));
				const size_t icpCells(icpId);
				Ucalc_nplus1[rfcFaces] = U_n[rfcFaces] - (options.deltat / deltax[icCells]) * (U_n[rfcFaces] * TU1 - g * (H_nplus1[icpCells] - H_nplus1[icCells])) - (options.deltat / deltay[icCells]) * (V1 * TV1);
			}
			double TV2(0.0);
			double TU2(0.0);
			double U1(0.0);
			{
				const Id lfcId(mesh->getLeftFaceOfCell(icId));
				const size_t lfcFaces(lfcId);
				const Id ictId(mesh->getTopCell(icId));
				const Id rfctId(mesh->getRightFaceOfCell(ictId));
				const size_t rfctFaces(rfctId);
				const Id lfctId(mesh->getLeftFaceOfCell(ictId));
				const size_t lfctFaces(lfctId);
				U1 = (U_n[rfcFaces] + U_n[lfcFaces] + U_n[rfctFaces] + U_n[lfctFaces]) / 4;
			}
			if (U1 <= 0) 
			{
				const Id icpId(mesh->getRightCell(icId));
				const Id tfcpId(mesh->getTopFaceOfCell(icpId));
				const size_t tfcpFaces(tfcpId);
				TU2 = U_n[tfcpFaces] - U_n[tfcFaces];
			}
			else
			{
				const Id icmId(mesh->getLeftCell(icId));
				const Id tfcmId(mesh->getTopFaceOfCell(icmId));
				const size_t tfcmFaces(tfcmId);
				TU2 = U_n[tfcFaces] - U_n[tfcmFaces];
			}
			if (U_n[tfcFaces] <= 0) 
			{
				const Id icpId(mesh->getTopCell(icId));
				const Id tfcpId(mesh->getTopFaceOfCell(icpId));
				const size_t tfcpFaces(tfcpId);
				const Id bfcpId(mesh->getBottomFaceOfCell(icpId));
				const size_t bfcpFaces(bfcpId);
				TV2 = U_n[tfcpFaces] - U_n[bfcpFaces];
			}
			else
			{
				const Id bfcId(mesh->getBottomFaceOfCell(icId));
				const size_t bfcFaces(bfcId);
				TV2 = U_n[tfcFaces] - U_n[bfcFaces];
			}
			{
				const Id icpId(mesh->getTopCell(icId));
				const size_t icpCells(icpId);
				Ucalc_nplus1[tfcFaces] = U_n[tfcFaces] - (options.deltat / deltay[icCells]) * (U_n[tfcFaces] * TV2 - g * (H_nplus1[icpCells] - H_nplus1[icCells])) - (options.deltat / deltax[icCells]) * (U1 * TU2);
			}
		});
	}
}

/**
 * Job setUpTimeLoopN called @5.0 in simulate method.
 * In variables: Dij_n0, Dt_n0, H_n0, Hcalc_n0, U_n0, Ucalc_n0, t_n0
 * Out variables: Dij_n, Dt_n, H_n, Hcalc_n, U_n, Ucalc_n, t_n
 */
void Schema2::setUpTimeLoopN() noexcept
{
	t_n = t_n0;
	parallel_exec(nbFaces, [&](const size_t& i1Faces)
	{
		U_n[i1Faces] = U_n0[i1Faces];
	});
	parallel_exec(nbFaces, [&](const size_t& i1Faces)
	{
		Ucalc_n[i1Faces] = Ucalc_n0[i1Faces];
	});
	parallel_exec(nbCells, [&](const size_t& i1Cells)
	{
		H_n[i1Cells] = H_n0[i1Cells];
	});
	parallel_exec(nbCells, [&](const size_t& i1Cells)
	{
		Hcalc_n[i1Cells] = Hcalc_n0[i1Cells];
	});
	parallel_exec(nbCells, [&](const size_t& i1Cells)
	{
		Dij_n[i1Cells] = Dij_n0[i1Cells];
	});
	parallel_exec(nbCells, [&](const size_t& i1Cells)
	{
		Dt_n[i1Cells] = Dt_n0[i1Cells];
	});
}

/**
 * Job updateUrunup called @5.0 in executeTimeLoopN method.
 * In variables: Ucalc_nplus1
 * Out variables: Urn_nplus1
 */
void Schema2::updateUrunup() noexcept
{
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		parallel_exec(nbInnerCells, [&](const size_t& icInnerCells)
		{
			const Id icId(innerCells[icInnerCells]);
			const Id rId(mesh->getRightFaceOfCell(icId));
			const size_t rFaces(rId);
			Urn_nplus1[rFaces] = Ucalc_nplus1[rFaces];
		});
	}
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		parallel_exec(nbInnerCells, [&](const size_t& icInnerCells)
		{
			const Id icId(innerCells[icInnerCells]);
			const Id lId(mesh->getLeftFaceOfCell(icId));
			const size_t lFaces(lId);
			Urn_nplus1[lFaces] = Ucalc_nplus1[lFaces];
		});
	}
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		parallel_exec(nbInnerCells, [&](const size_t& icInnerCells)
		{
			const Id icId(innerCells[icInnerCells]);
			const Id bId(mesh->getBottomFaceOfCell(icId));
			const size_t bFaces(bId);
			Urn_nplus1[bFaces] = Ucalc_nplus1[bFaces];
		});
	}
	{
		const auto innerCells(mesh->getInnerCells());
		const size_t nbInnerCells(innerCells.size());
		parallel_exec(nbInnerCells, [&](const size_t& icInnerCells)
		{
			const Id icId(innerCells[icInnerCells]);
			const Id tId(mesh->getTopFaceOfCell(icId));
			const size_t tFaces(tId);
			Urn_nplus1[tFaces] = Ucalc_nplus1[tFaces];
		});
	}
}

/**
 * Job executeTimeLoopN called @6.0 in simulate method.
 * In variables: Dij_n, Dij_nplus1, Dt_n, H_n, H_nplus1, Hcalc_nplus1, Hru_nplus1, U_n, Ucalc_nplus1, Urn_nplus1, deltat, deltax, deltay, g, t_n
 * Out variables: Dij_nplus1, Dt_nplus1, H_nplus1, Hcalc_nplus1, Hplot_nplus1, Hru_nplus1, U_nplus1, Ucalc_nplus1, Urn_nplus1, t_nplus1
 */
void Schema2::executeTimeLoopN() noexcept
{
	n = 0;
	bool continueLoop = true;
	do
	{
		globalTimer.start();
		cpuTimer.start();
		n++;
		if (!writer.isDisabled() && n >= lastDump + options.outputPeriod)
			dumpVariables(n);
		if (n!=1)
			std::cout << "[" << __CYAN__ << __BOLD__ << setw(3) << n << __RESET__ "] t = " << __BOLD__
				<< setiosflags(std::ios::scientific) << setprecision(8) << setw(16) << t_n << __RESET__;
	
		computeTn(); // @1.0
		updateDij(); // @1.0
		updateHcalc(); // @1.0
		updateDtot(); // @2.0
		updateHru(); // @2.0
		updateHinner(); // @3.0
		updateHouter(); // @3.0
		updateHplot(); // @3.0
		updateUcalc(); // @4.0
		updateUrunup(); // @5.0
		updateUinner(); // @6.0
		updateUouter(); // @6.0
		
	
		// Evaluate loop condition with variables at time n
		continueLoop = (t_nplus1 < options.stopTime && n < options.maxIter);
	
		if (continueLoop)
		{
			t_n = t_nplus1;
			parallel_exec(nbFaces, [&](const size_t& i1Faces)
			{
				U_n[i1Faces] = U_nplus1[i1Faces];
			});
			parallel_exec(nbFaces, [&](const size_t& i1Faces)
			{
				Ucalc_n[i1Faces] = Ucalc_nplus1[i1Faces];
			});
			parallel_exec(nbFaces, [&](const size_t& i1Faces)
			{
				Urn_n[i1Faces] = Urn_nplus1[i1Faces];
			});
			parallel_exec(nbCells, [&](const size_t& i1Cells)
			{
				H_n[i1Cells] = H_nplus1[i1Cells];
			});
			parallel_exec(nbCells, [&](const size_t& i1Cells)
			{
				Hcalc_n[i1Cells] = Hcalc_nplus1[i1Cells];
			});
			parallel_exec(nbCells, [&](const size_t& i1Cells)
			{
				Hru_n[i1Cells] = Hru_nplus1[i1Cells];
			});
			parallel_exec(nbCells, [&](const size_t& i1Cells)
			{
				Hplot_n[i1Cells] = Hplot_nplus1[i1Cells];
			});
			parallel_exec(nbCells, [&](const size_t& i1Cells)
			{
				Dij_n[i1Cells] = Dij_nplus1[i1Cells];
			});
			parallel_exec(nbCells, [&](const size_t& i1Cells)
			{
				Dt_n[i1Cells] = Dt_nplus1[i1Cells];
			});
		}
	
		cpuTimer.stop();
		globalTimer.stop();
	
		// Timers display
		if (!writer.isDisabled())
			std::cout << " {CPU: " << __BLUE__ << cpuTimer.print(true) << __RESET__ ", IO: " << __BLUE__ << ioTimer.print(true) << __RESET__ "} ";
		else
			std::cout << " {CPU: " << __BLUE__ << cpuTimer.print(true) << __RESET__ ", IO: " << __RED__ << "none" << __RESET__ << "} ";
		
		// Progress
		std::cout << progress_bar(n, options.maxIter, t_n, options.stopTime, 25);
		std::cout << __BOLD__ << __CYAN__ << Timer::print(
			eta(n, options.maxIter, t_n, options.stopTime, options.deltat, globalTimer), true)
			<< __RESET__ << "\r";
		std::cout.flush();
	
		cpuTimer.reset();
		ioTimer.reset();
	} while (continueLoop);
	// force a last output at the end
	dumpVariables(n, false);
}

/**
 * Job updateUinner called @6.0 in executeTimeLoopN method.
 * In variables: Urn_nplus1
 * Out variables: U_nplus1
 */
void Schema2::updateUinner() noexcept
{
	parallel_exec(nbFaces, [&](const size_t& icFaces)
	{
		U_nplus1[icFaces] = Urn_nplus1[icFaces];
	});
}

/**
 * Job updateUouter called @6.0 in executeTimeLoopN method.
 * In variables: Urn_nplus1
 * Out variables: U_nplus1
 */
void Schema2::updateUouter() noexcept
{
	{
		const auto topCells(mesh->getTopCells());
		const size_t nbTopCells(topCells.size());
		parallel_exec(nbTopCells, [&](const size_t& tcTopCells)
		{
			const Id tcId(topCells[tcTopCells]);
			const Id rfId(mesh->getRightFaceOfCell(tcId));
			const size_t rfFaces(rfId);
			const Id bcId(mesh->getBottomCell(tcId));
			const Id brfId(mesh->getRightFaceOfCell(bcId));
			const size_t brfFaces(brfId);
			U_nplus1[rfFaces] = Urn_nplus1[brfFaces];
		});
	}
	{
		const auto bottomCells(mesh->getBottomCells());
		const size_t nbBottomCells(bottomCells.size());
		parallel_exec(nbBottomCells, [&](const size_t& bcBottomCells)
		{
			const Id bcId(bottomCells[bcBottomCells]);
			const Id rfId(mesh->getRightFaceOfCell(bcId));
			const size_t rfFaces(rfId);
			const Id bcfId(mesh->getTopCell(bcId));
			const Id trfId(mesh->getRightFaceOfCell(bcfId));
			const size_t trfFaces(trfId);
			U_nplus1[rfFaces] = Urn_nplus1[trfFaces];
		});
	}
	{
		const auto leftCells(mesh->getLeftCells());
		const size_t nbLeftCells(leftCells.size());
		parallel_exec(nbLeftCells, [&](const size_t& lcLeftCells)
		{
			const Id lcId(leftCells[lcLeftCells]);
			const Id lfId(mesh->getLeftFaceOfCell(lcId));
			const size_t lfFaces(lfId);
			const Id rfId(mesh->getRightFaceOfCell(lcId));
			const size_t rfFaces(rfId);
			U_nplus1[lfFaces] = Urn_nplus1[rfFaces];
		});
	}
	{
		const auto rightCells(mesh->getRightCells());
		const size_t nbRightCells(rightCells.size());
		parallel_exec(nbRightCells, [&](const size_t& rcRightCells)
		{
			const Id rcId(rightCells[rcRightCells]);
			const Id rfId(mesh->getRightFaceOfCell(rcId));
			const size_t rfFaces(rfId);
			const Id lfId(mesh->getLeftFaceOfCell(rcId));
			const size_t lfFaces(lfId);
			U_nplus1[rfFaces] = Urn_nplus1[lfFaces];
		});
	}
}

void Schema2::dumpVariables(int iteration, bool useTimer)
{
	if (!writer.isDisabled())
	{
		if (useTimer)
		{
			cpuTimer.stop();
			ioTimer.start();
		}
		auto quads = mesh->getGeometry()->getQuads();
		writer.startVtpFile(iteration, t_n, nbNodes, X.data(), nbCells, quads.data());
		writer.openNodeData();
		writer.closeNodeData();
		writer.openCellData();
		writer.openCellArray("hauteur", 0);
		for (size_t i=0 ; i<nbCells ; ++i)
			writer.write(H_n[i]);
		writer.closeCellArray();
		writer.openCellArray("hplot", 0);
		for (size_t i=0 ; i<nbCells ; ++i)
			writer.write(Hplot_n[i]);
		writer.closeCellArray();
		writer.openCellArray("Dt", 0);
		for (size_t i=0 ; i<nbCells ; ++i)
			writer.write(Dt_n[i]);
		writer.closeCellArray();
		writer.closeCellData();
		writer.closeVtpFile();
		lastDump = n;
		if (useTimer)
		{
			ioTimer.stop();
			cpuTimer.start();
		}
	}
}

void Schema2::simulate()
{
	std::cout << "\n" << __BLUE_BKG__ << __YELLOW__ << __BOLD__ <<"\tStarting Schema2 ..." << __RESET__ << "\n\n";
	
	std::cout << "[" << __GREEN__ << "TOPOLOGY" << __RESET__ << "]  HWLOC unavailable cannot get topological informations" << std::endl;
	
	if (!writer.isDisabled())
		std::cout << "[" << __GREEN__ << "OUTPUT" << __RESET__ << "]    VTK files stored in " << __BOLD__ << writer.outputDirectory() << __RESET__ << " directory" << std::endl;
	else
		std::cout << "[" << __GREEN__ << "OUTPUT" << __RESET__ << "]    " << __BOLD__ << "Disabled" << __RESET__ << std::endl;

	iniCenter(); // @1.0
	initTime(); // @1.0
	initUini(); // @1.0
	initXc(); // @1.0
	initDijini(); // @2.0
	initHini(); // @2.0
	initU(); // @2.0
	initdeltaxdeltay(); // @2.0
	initDij(); // @3.0
	initH(); // @3.0
	initUcalc(); // @3.0
	iniDt(); // @4.0
	initHcalc(); // @4.0
	setUpTimeLoopN(); // @5.0
	executeTimeLoopN(); // @6.0
	
	std::cout << __YELLOW__ << "\n\tDone ! Took " << __MAGENTA__ << __BOLD__ << globalTimer.print() << __RESET__ << std::endl;
}

int main(int argc, char* argv[]) 
{
	string dataFile;
	int ret = 0;
	
	if (argc == 2)
	{
		dataFile = argv[1];
	}
	else
	{
		std::cerr << "[ERROR] Wrong number of arguments. Expecting 1 arg: dataFile." << std::endl;
		std::cerr << "(Schema2.json)" << std::endl;
		return -1;
	}
	
	// read json dataFile
	ifstream ifs(dataFile);
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document d;
	d.ParseStream(isw);
	assert(d.IsObject());
	
	// Mesh instanciation
	CartesianMesh2DFactory meshFactory;
	if (d.HasMember("mesh"))
	{
		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		d["mesh"].Accept(writer);
		meshFactory.jsonInit(strbuf.GetString());
	}
	CartesianMesh2D* mesh = meshFactory.create();
	
	// Module instanciation(s)
	Schema2::Options schema2Options;
	if (d.HasMember("schema2"))
	{
		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		d["schema2"].Accept(writer);
		schema2Options.jsonInit(strbuf.GetString());
	}
	Schema2* schema2 = new Schema2(mesh, schema2Options);
	
	// Start simulation
	// Simulator must be a pointer when a finalize is needed at the end (Kokkos, omp...)
	schema2->simulate();
	
	delete schema2;
	delete mesh;
	return ret;
}
