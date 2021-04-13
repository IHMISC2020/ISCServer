#include "DataCalibrageHandler.h"

/*static*/DataCalibrageHandler* DataCalibrageHandler::mInstance = nullptr;


DataCalibrageHandler::DataCalibrageHandler() {}
/*virtual*/DataCalibrageHandler::~DataCalibrageHandler() {}

/*static*/ DataCalibrageHandler& DataCalibrageHandler::getInstance() {
	if (mInstance == nullptr) mInstance = new DataCalibrageHandler;
	return *mInstance;
}

const std::vector<DataCalibrage>& DataCalibrageHandler::getDataCalibrage() const {
	return mDataCalibrages;
}