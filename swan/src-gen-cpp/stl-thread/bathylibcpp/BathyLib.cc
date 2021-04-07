#include "BathyLib.h"
#include "netcdf.h"
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

void BathyLib::jsonInit(const char* jsonContent)
{
	rapidjson::Document document;
	assert(!document.Parse(jsonContent).HasParseError());
	assert(document.IsObject());
	const rapidjson::Value::Object& o = document.GetObject();

	if (o.HasMember("waveFilename"))
	{
		const rapidjson::Value& valueof_fileName = o["waveFilename"];
		assert(valueof_fileName.IsString());
		waveFilename = valueof_fileName.GetString();
	}

	if (o.HasMember("waveVarName"))
	{
		const rapidjson::Value& valueof_fileName = o["waveVarName"];
		assert(valueof_fileName.IsString());
		waveVarName = valueof_fileName.GetString();
	}

	if (o.HasMember("depthFilename"))
	{
		const rapidjson::Value& valueof_fileName = o["depthFilename"];
		assert(valueof_fileName.IsString());
		depthFilename = valueof_fileName.GetString();
	}

	if (o.HasMember("depthVarName"))
	{
		const rapidjson::Value& valueof_fileName = o["depthVarName"];
		assert(valueof_fileName.IsString());
		depthVarName = valueof_fileName.GetString();
	}

	if (o.HasMember("lonFilename"))
	{
		const rapidjson::Value& valueof_fileName = o["lonFilename"];
		assert(valueof_fileName.IsString());
		lonFilename = valueof_fileName.GetString();
	}

	if (o.HasMember("lonVarName"))
	{
		const rapidjson::Value& valueof_fileName = o["lonVarName"];
		assert(valueof_fileName.IsString());
		lonVarName = valueof_fileName.GetString();
	}

	if (o.HasMember("latFilename"))
	{
		const rapidjson::Value& valueof_fileName = o["latFilename"];
		assert(valueof_fileName.IsString());
		latFilename = valueof_fileName.GetString();
	}

	if (o.HasMember("latVarName"))
	{
		const rapidjson::Value& valueof_fileName = o["latVarName"];
		assert(valueof_fileName.IsString());
		latVarName = valueof_fileName.GetString();
	}

	if (o.HasMember("bottomMotionFilename"))
	{
		const rapidjson::Value& valueof_fileName = o["bottomMotionFilename"];
		assert(valueof_fileName.IsString());
		bottomMotionFilename = valueof_fileName.GetString();
	}

	if (o.HasMember("bottomVarName"))
	{
		const rapidjson::Value& valueof_fileName = o["bottomVarName"];
		assert(valueof_fileName.IsString());
		bottomVarName = valueof_fileName.GetString();
	}
}

double BathyLib::nextWaveHeight()
{
	if(dataWave != NULL)
	{
		waveHeight = dataWave[countWave++];
		if(countWave != countWaveMax)
			return waveHeight;
		else
		{
			free(dataWave);
			return waveHeight;
		}
	}
	else
	{
		int ncid, varid, retval, n;
		size_t* len;

		//ouvre le fichier
		replaceHomeVar(waveFilename);
		if((retval = nc_open(waveFilename.c_str(), NC_NOWRITE, &ncid)))
		{std::cout << retval <<"error nc open nextWaveHeight"<< std::endl; exit(retval);}

		//recupere l'ID de la data nommé ${waveVarName}
		if((retval = nc_inq_varid(ncid, waveVarName.c_str(), &varid)))
		{std::cout << retval <<"  error nc inq varid WaveVarName nextWaveHeight"<< std::endl; exit(retval);}

		// recupere le nombre de dimension
		nc_inq_ndims(ncid, &n);
		len = (size_t*)malloc(n * sizeof(size_t));

		//recupere les length des dimensions
		for(int i = 0 ; i < n ; i++)
			nc_inq_dimlen(ncid, i, len+i);

		for(int i = 0 ; i < n ; i++)
		{std::cout << "dim"<<i<< "_len = "<< *(len+i) << std::endl; countWaveMax *= *(len+i);}

		// allouer la bonne taille
		dataWave = (float*)malloc(countWaveMax * sizeof(float));

		// recupere les data
		if((retval = nc_get_var_float(ncid, varid, dataWave)))
		{std::cout << "error get var float nextWaveHeight" << std::endl; exit(retval);}

		// liberer la memoire
		nc_close(ncid);
		free(len);

		waveHeight = dataWave[countWave++];
		return waveHeight;
	}
}

double BathyLib::nextDepth()
{
	if(dataDepth != NULL)
	{
		depth = dataDepth[countDepth++];
		if(countDepth != countDepthMax)
			return depth;
		else
		{
			free(dataDepth);
			return depth;
		}
	}
	else
	{
		int ncid, varid, retval, n;
		size_t* len;

		//ouvre le fichier
		replaceHomeVar(depthFilename);
		if((retval = nc_open(depthFilename.c_str(), NC_NOWRITE, &ncid)))
		{std::cout << retval <<"error nc open nextDepth"<< std::endl; exit(retval);}

		//recupere l'ID de la data nommé ${depthVarName}
		if((retval = nc_inq_varid(ncid, depthVarName.c_str(), &varid)))
		{std::cout << retval <<"  error nc inq varid depthVarName nextDepth"<< std::endl; exit(retval);}

		// recupere le nombre de dimension
		nc_inq_ndims(ncid, &n);
		len = (size_t*)malloc(n * sizeof(size_t));

		//recupere les length des dimensions
		for(int i = 0 ; i < n ; i++)
			nc_inq_dimlen(ncid, i, len+i);

		for(int i = 0 ; i < n ; i++)
		{std::cout << "dim"<<i<< "_len = "<< *(len+i) << std::endl; countDepthMax *= *(len+i);}

		// allouer la bonne taille
		dataDepth = (float*)malloc(countDepthMax * sizeof(float));

		// recupere les data
		if((retval = nc_get_var_float(ncid, varid, dataDepth)))
		{std::cout << "error get var float nextDepth" << std::endl; exit(retval);}

		// liberer la memoire
		nc_close(ncid);
		free(len);

		depth = dataDepth[countDepth++];
		return depth;
	}
}

double BathyLib::nextLat()
{
	if(dataLat != NULL)
	{
		lat = dataLat[countLat++];
		if(countLat != countLatMax)
			return lat;
		else
		{
			free(dataLat);
			return lat;
		}
	}
	else
	{
		int ncid, varid, lonid, latid, retval, n;
		size_t* len;
		size_t nbLon, nbLat;

		//ouvre le fichier
		replaceHomeVar(latFilename);
		if((retval = nc_open(latFilename.c_str(), NC_NOWRITE, &ncid)))
		{std::cout << retval <<"error nc open nextLat"<< std::endl; exit(retval);}

		//recupere l'ID de la data nommé "lat"
		if((retval = nc_inq_varid(ncid, latVarName.c_str(), &varid)))
		{std::cout << retval <<"  error nc inq varid nextLat"<< std::endl; exit(retval);}

		//recupere le nombre de dimension
		nc_inq_ndims(ncid, &n);
		len = (size_t*)malloc(n * sizeof(size_t));

		//recupere les length des dimensions
		for(int i = 0 ; i < n ; i++)
			nc_inq_dimlen(ncid, i, len+i);

		for(int i = 0 ; i < n ; i++)
		{std::cout << "dim"<<i<< "_len = "<< *(len+i) << std::endl; countLatMax *= *(len+i);}

		// allouer le tableau de donnees
		dataLat = (float*)malloc(countLatMax * sizeof(float));

		//recuperer nb_lon et nb_lat
		nc_inq_dimid(ncid, lonVarName.c_str(), &lonid);
		nc_inq_dimid(ncid, latVarName.c_str(), &latid);
		nc_inq_dimlen(ncid, lonid, &nbLon);
		nc_inq_dimlen(ncid, latid, &nbLat);

		//creer un tableau temporaire de taille "nb_latitude"
		float* tmpTab = (float*)malloc(sizeof(float) * nbLat);

		//recupere les data dans un tableau temporaire de taille "nb_latitude"
		if((retval = nc_get_var_float(ncid, varid, tmpTab)))
		{std::cout << "error get var float nextLat" << std::endl; exit(retval);}

		//creer le tableau data_lat à l'aide de nb_lat et nb_lon
		for(size_t i = 0 ; i < nbLat ; i++)
			for(size_t j = 0 ; j < nbLon ; j++)
				dataLat[i * nbLon + j] = tmpTab[i];

		//liberer la memoire
		nc_close(ncid);
		free(len);
		free(tmpTab);

		lat = dataLat[countLat++];
		return lat;
	}
}

double BathyLib::nextLon()
{
	if(dataLon != NULL)
	{
		lon = dataLon[countLon++];
		if(countLon != countLonMax)
			return lon;
		else
		{
			free(dataLon);
			return lon;
		}
	}
	else
	{
		int ncid, varid, lonid, latid, retval, n;
		size_t* len;
		size_t nbLon, nbLat;

		//ouvre le fichier
		replaceHomeVar(lonFilename);
		if((retval = nc_open(lonFilename.c_str(), NC_NOWRITE, &ncid)))
		{std::cout << retval <<"error nc open lon nextLon"<< std::endl; exit(retval);}

		//recupere l'ID de la data nommé "lon"
		if((retval = nc_inq_varid(ncid, lonVarName.c_str(), &varid)))
		{std::cout << retval <<"  error nc inq varid nextLon"<< std::endl; exit(retval);}

		//recupere le nombre de dimension
		nc_inq_ndims(ncid, &n);
		len = (size_t*)malloc(n * sizeof(size_t));

		//recupere les length des dimensions
		for(int i = 0 ; i < n ; i++)
			nc_inq_dimlen(ncid, i, len+i);

		for(int i = 0 ; i < n ; i++)
		{std::cout << "dim"<<i<< "_len = "<< *(len+i) << std::endl; countLonMax *= *(len+i);}

		//allouer le tableau de donnees
		dataLon = (float*)malloc(countLonMax * sizeof(float));

		//recuperer nb_lon et nb_lat
		nc_inq_dimid(ncid, lonVarName.c_str(), &lonid);
		nc_inq_dimid(ncid, latVarName.c_str(), &latid);
		nc_inq_dimlen(ncid, lonid, &nbLon);
		nc_inq_dimlen(ncid, latid, &nbLat);

		//creer un tableau temporaire de taille "nb_longitude"
		float* tmpTab = (float*)malloc(sizeof(float) * nbLon);

		//recupere les data dans un tableau temporaire de taille "nb_longitude"
		if((retval = nc_get_var_float(ncid, varid, tmpTab)))
		{std::cout << "error get var float nextLon" << std::endl; exit(retval);}

		//creer le tableau data_lon à l'aide de nb_lat et nb_lon
		for(size_t i = 0 ; i < nbLat ; i++)
			memcpy(dataLon + i * nbLon, tmpTab, nbLon * sizeof(float));

		//liberer la memoire
		nc_close(ncid);
		free(len);
		free(tmpTab);

		lon = dataLon[countLon++];
		return lon;
	}
}
