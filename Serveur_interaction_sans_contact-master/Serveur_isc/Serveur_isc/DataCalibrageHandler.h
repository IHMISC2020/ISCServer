#pragma once

#include <vector>

#include "DataCalibrage.h"

class DataCalibrageHandler
{
private:
	static DataCalibrageHandler* mInstance;
	std::vector<DataCalibrage> mDataCalibrages;
public:
	DataCalibrageHandler();
	virtual ~DataCalibrageHandler();

	static DataCalibrageHandler& getInstance();
	const std::vector<DataCalibrage>& getDataCalibrage() const;

	void addData(const DataCalibrage& data) { mDataCalibrages.push_back(data); }
	void clearDatas() { mDataCalibrages.clear(); }

	static void deleteInstance() {
		delete mInstance;
		mInstance = nullptr;
	}
};