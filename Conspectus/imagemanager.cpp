#include "imagemanager.h"

ImageManager::ImageManager(QImage *image_name, QObject *parent) : image(image_name), QObject(parent){}

ImageManager::~ImageManager(){}


