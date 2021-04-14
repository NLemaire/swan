/* DO NOT EDIT THIS FILE - it is machine generated */

#include "Schema1.h"
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


/******************** Free functions definitions ********************/

namespace schema1freefuncs
{
double sumR0(double a, double b)
{
	return a + b;
}
}

/******************** Options definition ********************/

void
Schema1::Options::jsonInit(const char* jsonContent)
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
	// maxIter
	if (o.HasMember("maxIter"))
	{
		const rapidjson::Value& valueof_maxIter = o["maxIter"];
		assert(valueof_maxIter.IsInt());
		maxIter = valueof_maxIter.GetInt();
	}
	else
		maxIter = 200;
	// maxTime
	if (o.HasMember("maxTime"))
	{
		const rapidjson::Value& valueof_maxTime = o["maxTime"];
		assert(valueof_maxTime.IsDouble());
		maxTime = valueof_maxTime.GetDouble();
	}
	else
		maxTime = 6000.0;
	// X0
	if (o.HasMember("X0"))
	{
		const rapidjson::Value& valueof_X0 = o["X0"];
		assert(valueof_X0.IsDouble());
		X0 = valueof_X0.GetDouble();
	}
	else
		X0 = 25000.0;
	// Sigma
	if (o.HasMember("Sigma"))
	{
		const rapidjson::Value& valueof_Sigma = o["Sigma"];
		assert(valueof_Sigma.IsDouble());
		Sigma = valueof_Sigma.GetDouble();
	}
	else
		Sigma = 5000.0;
	// Amp
	if (o.HasMember("Amp"))
	{
		const rapidjson::Value& valueof_Amp = o["Amp"];
		assert(valueof_Amp.IsDouble());
		Amp = valueof_Amp.GetDouble();
	}
	else
		Amp = 0.2;
	// deltat
	if (o.HasMember("deltat"))
	{
		const rapidjson::Value& valueof_deltat = o["deltat"];
		assert(valueof_deltat.IsDouble());
		deltat = valueof_deltat.GetDouble();
	}
	else
		deltat = 1.0;
}

/******************** Module definition ********************/

Schema1::Schema1(CartesianMesh2D* aMesh, Options& aOptions)
: mesh(aMesh)
, nbNodes(mesh->getNbNodes())
, nbCells(mesh->getNbCells())
, nbNodesOfCell(CartesianMesh2D::MaxNbNodesOfCell)
, options(aOptions)
, writer("Schema1", options.outputPath)
, lastDump(numeric_limits<int>::min())
, X(nbNodes)
, H_n(nbCells)
, H_nplus1(nbCells)
, H_n0(nbCells)
, U_n(nbCells)
, U_nplus1(nbCells)
, U_n0(nbCells)
, center(nbCells)
{
	// Copy node coordinates
	const auto& gNodes = mesh->getGeometry()->getNodes();
	for (size_t rNodes=0; rNodes<nbNodes; rNodes++)
	{
		X[rNodes][0] = gNodes[rNodes][0];
		X[rNodes][1] = gNodes[rNodes][1];
	}
}

Schema1::~Schema1()
{
}

/**
 * Job computeHn called @1.0 in executeTimeLoopN method.
 * In variables: D, H_n, U_n, deltat, deltax
 * Out variables: H_nplus1
 */
void Schema1::computeHn() noexcept
{
	parallel_exec(nbCells, [&](const size_t& icCells)
	{
		const Id icId(icCells);
		const Id rcId(mesh->getRightCell(icId));
		const size_t rcCells(rcId);
		const Id lcId(mesh->getLeftCell(icId));
		const size_t lcCells(lcId);
		H_nplus1[icCells] = H_n[icCells] - (options.deltat / deltax) * ((U_n[rcCells] * (H_n[rcCells] + D)) - (U_n[lcCells] * (H_n[lcCells] + D)));
	});
}

/**
 * Job computeTn called @1.0 in executeTimeLoopN method.
 * In variables: deltat, t_n
 * Out variables: t_nplus1
 */
void Schema1::computeTn() noexcept
{
	t_nplus1 = t_n + options.deltat;
}

/**
 * Job computeUn called @1.0 in executeTimeLoopN method.
 * In variables: H_n, U_n, deltat, deltax, g
 * Out variables: U_nplus1
 */
void Schema1::computeUn() noexcept
{
	parallel_exec(nbCells, [&](const size_t& icCells)
	{
		const Id icId(icCells);
		const Id rcId(mesh->getRightCell(icId));
		const size_t rcCells(rcId);
		const Id lcId(mesh->getLeftCell(icId));
		const size_t lcCells(lcId);
		U_nplus1[icCells] = U_n[icCells] - (options.deltat / deltax) * g * (H_n[rcCells] - H_n[lcCells]);
	});
}

/**
 * Job iniCenter called @1.0 in simulate method.
 * In variables: X
 * Out variables: center
 */
void Schema1::iniCenter() noexcept
{
	parallel_exec(nbCells, [&](const size_t& jCells)
	{
		const Id jId(jCells);
		double reduction0(0.0);
		{
			const auto nodesOfCellJ(mesh->getNodesOfCell(jId));
			const size_t nbNodesOfCellJ(nodesOfCellJ.size());
			for (size_t rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
			{
				const Id rId(nodesOfCellJ[rNodesOfCellJ]);
				const size_t rNodes(rId);
				reduction0 = schema1freefuncs::sumR0(reduction0, X[rNodes][0]);
			}
		}
		center[jCells] = 0.25 * reduction0;
	});
}

/**
 * Job initU called @1.0 in simulate method.
 * In variables: 
 * Out variables: U_n0
 */
void Schema1::initU() noexcept
{
	parallel_exec(nbCells, [&](const size_t& icCells)
	{
		U_n0[icCells] = 0.0;
	});
}

/**
 * Job initH called @2.0 in simulate method.
 * In variables: Amp, Sigma, X0, center
 * Out variables: H_n0
 */
void Schema1::initH() noexcept
{
	parallel_exec(nbCells, [&](const size_t& icCells)
	{
		H_n0[icCells] = options.Amp * std::exp(-0.5 * (center[icCells] - options.X0) * (center[icCells] - options.X0) / (options.Sigma * options.Sigma));
	});
}

/**
 * Job setUpTimeLoopN called @3.0 in simulate method.
 * In variables: H_n0, U_n0
 * Out variables: H_n, U_n
 */
void Schema1::setUpTimeLoopN() noexcept
{
	for (size_t i1(0) ; i1<H_n.size() ; i1++)
		H_n[i1] = H_n0[i1];
	for (size_t i1(0) ; i1<U_n.size() ; i1++)
		U_n[i1] = U_n0[i1];
}

/**
 * Job executeTimeLoopN called @4.0 in simulate method.
 * In variables: D, H_n, U_n, deltat, deltax, g, t_n
 * Out variables: H_nplus1, U_nplus1, t_nplus1
 */
void Schema1::executeTimeLoopN() noexcept
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
	
		computeHn(); // @1.0
		computeTn(); // @1.0
		computeUn(); // @1.0
		
	
		// Evaluate loop condition with variables at time n
		continueLoop = (n + 1 < options.maxIter && t_nplus1 < options.maxTime);
	
		if (continueLoop)
		{
			// Switch variables to prepare next iteration
			std::swap(t_nplus1, t_n);
			std::swap(H_nplus1, H_n);
			std::swap(U_nplus1, U_n);
		}
	
		cpuTimer.stop();
		globalTimer.stop();
	
		// Timers display
		if (!writer.isDisabled())
			std::cout << " {CPU: " << __BLUE__ << cpuTimer.print(true) << __RESET__ ", IO: " << __BLUE__ << ioTimer.print(true) << __RESET__ "} ";
		else
			std::cout << " {CPU: " << __BLUE__ << cpuTimer.print(true) << __RESET__ ", IO: " << __RED__ << "none" << __RESET__ << "} ";
		
		// Progress
		std::cout << progress_bar(n, options.maxIter, t_n, options.maxTime, 25);
		std::cout << __BOLD__ << __CYAN__ << Timer::print(
			eta(n, options.maxIter, t_n, options.maxTime, options.deltat, globalTimer), true)
			<< __RESET__ << "\r";
		std::cout.flush();
	
		cpuTimer.reset();
		ioTimer.reset();
	} while (continueLoop);
	// force a last output at the end
	dumpVariables(n, false);
}

void Schema1::dumpVariables(int iteration, bool useTimer)
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

void Schema1::simulate()
{
	std::cout << "\n" << __BLUE_BKG__ << __YELLOW__ << __BOLD__ <<"\tStarting Schema1 ..." << __RESET__ << "\n\n";
	
	std::cout << "[" << __GREEN__ << "TOPOLOGY" << __RESET__ << "]  HWLOC unavailable cannot get topological informations" << std::endl;
	
	if (!writer.isDisabled())
		std::cout << "[" << __GREEN__ << "OUTPUT" << __RESET__ << "]    VTK files stored in " << __BOLD__ << writer.outputDirectory() << __RESET__ << " directory" << std::endl;
	else
		std::cout << "[" << __GREEN__ << "OUTPUT" << __RESET__ << "]    " << __BOLD__ << "Disabled" << __RESET__ << std::endl;

	iniCenter(); // @1.0
	initU(); // @1.0
	initH(); // @2.0
	setUpTimeLoopN(); // @3.0
	executeTimeLoopN(); // @4.0
	
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
		std::cerr << "(Schema1.json)" << std::endl;
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
	Schema1::Options schema1Options;
	if (d.HasMember("schema1"))
	{
		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		d["schema1"].Accept(writer);
		schema1Options.jsonInit(strbuf.GetString());
	}
	Schema1* schema1 = new Schema1(mesh, schema1Options);
	
	// Start simulation
	// Simulator must be a pointer when a finalize is needed at the end (Kokkos, omp...)
	schema1->simulate();
	
	delete schema1;
	delete mesh;
	return ret;
}
