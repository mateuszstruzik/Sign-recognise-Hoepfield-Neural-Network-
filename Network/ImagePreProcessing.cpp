#include "ImagePreProcessing.h"



void ImagePreProcessing::arrayprint(vector<vector<int>> imagetab)
{
	int is=imagetab.size();
	int js = imagetab[0].size();

	for (int i = 0; i < is; i++) {
		for (int j = 0; j < js; j++) {
			if (imagetab[i][j] == 1)
				std::cout << " " << imagetab[i][j] << " ";
			else
				std::cout << imagetab[i][j] << " ";
		}
		std::cout << std::endl;

	}
}

void ImagePreProcessing::coverImage(QImage & im, int a, int bb)
{
	QSize imsize = im.size();
	QColor col, col2, col3;
	int r, g, b, p;
	int i, j;

	if (a == 8)
		i = 0;
	else if (a == 16)
		i = 8;

	if (bb == 8)
		j = 0;
	else if (bb == 16)
		j = 8;

	for (i ; i < a; i++) {
		for (j ; j < bb; j++) {
			im.setPixel(i, j, 0);
		}
		if (bb == 8)
			j = 0;
		else if (bb == 16)
			j = 8;
		}
}
	



ImagePreProcessing::ImagePreProcessing(string fullpath)
{
	//stringstream s;
	//string ss;
	//s << "F:/softcomputing/" << name << ".png";
	//ss = s.str();
	processingimage.load(fullpath.c_str());
	processingimage_size = processingimage.size();
	width = processingimage_size.width(), height = processingimage_size.height();
	//s.str("");
}

void ImagePreProcessing::maskCreation(string name, string path, string format, string newname)
{
	stringstream s2;
	string ss2;
	s2 << path << name << format;
	ss2 = s2.str();
	s2.str("");
	processingimage.load(ss2.c_str());
	QImage binaryimage;
	for (int p1 = 0; p1 < width; p1++) {
		for (int p2 = 0; p2 < height; p2++) {
			qrgb = processingimage.pixel(p1, p2);

			processingimage.setPixel(p1, p2, QColor((qRed(qrgb) + qGreen(qrgb) + qBlue(qrgb)) / 3).rgb());
		}
	}

	if (name == "znak7" || name == "znak17" || name == "znak16" || name == "znak18" || name == "znak21" ||name== "znak21_ed") {
		binaryimage = processingimage.createMaskFromColor(processingimage.pixel(width / 2, height / 2), Qt::MaskOutColor);
	}
	else
		binaryimage = processingimage.createMaskFromColor(processingimage.pixel(width / 2, height / 2), Qt::MaskInColor);
	//name = "proba";
	stringstream s;
	string ss;
	s << path << "b_" << newname << format;
	ss = s.str();
	s.str("");
	binaryimage.save(ss.c_str());
}

void ImagePreProcessing::scaledImage(string name, string path, string format, string newname)
{

	stringstream s;
	string ss;
	s << path << name << format;
	ss = s.str();
	s.str("");
	

	QImage im2;
	im2.load(ss.c_str());
	QImage im = im2.scaled(newwidth, newheight, Qt::IgnoreAspectRatio);
	s<< path<<"scaled_" << newname << format;
	ss = s.str();
	s.str("");
	im.save(ss.c_str());


}

void ImagePreProcessing::convertImageToMatrix(string name, string path, string format )
{
	imagearray.resize(newwidth, vector<int>(newheight));
	stringstream s;
	string ss;

	s << path << name << format;
	ss = s.str();
	s.str("");
	processingimage.load(ss.c_str());
	QColor col;
	int r, g, b, p;

	for (int i = 0; i < newwidth; i++) {
		for (int j = 0; j < newheight; j++) {

			col = QColor::fromRgb(processingimage.pixel(i, j));
			col.getRgb(&r, &g, &b, &p);
			if (r == 0 && g == 0 && b == 0) {
				imagearray[i][j] = 1;
			}
			else
			{
				imagearray[i][j] = -1;
			}
		}
	}

	arrayprint(imagearray);
}

void ImagePreProcessing::retreievingImage(string name)
{
	QImage ret_image;
	ret_image.load(name.c_str());//"f:/softcomputing/scaled_znak21_edit.png"
	QSize size_ret_image = ret_image.size();

	retimagearray.resize(newwidth, (vector<int>(newheight)));

	QColor col_ret;
	int r, g, b, p;
	vector<int> ret_vect;

	for (int i = 0; i < newwidth; i++) {
		for (int j = 0; j < newheight; j++) {

			col_ret = QColor::fromRgb(ret_image.pixel(i, j));
			col_ret.getRgb(&r, &g, &b, &p);
			if (r == 0 && g == 0 && b == 0) {
				retimagearray[i][j] = 1;
			}
			else
			{
				retimagearray[i][j] = -1;
			}
		}
	}

	std::cout << std::endl;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (retimagearray[i][j] == 1)
				std::cout << " " << retimagearray[i][j] << " ";
			else
				std::cout << retimagearray[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
}

void ImagePreProcessing::noiseFunction(string fullpath,int pr,int c)
{
	stringstream s;
	string ss;

	s << fullpath << c << ".png";
	ss = s.str();
	s.str("");

	vector < vector<int>>proba(16, vector<int>(16));
	QImage image(16,16, QImage::Format_RGB888),newim;
	image.load(ss.c_str());
	QSize imsize = image.size();
	int h = imsize.height(), w = imsize.width();
	QColor col,col2,col3;
	int r, g, b, p;

	
	int coile = pr;
	int counting = 0;

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {

			if (counting == 0) {
				col = QColor::fromRgb(image.pixel(i, j));
				col.getRgb(&r, &g, &b, &p);

				if (r == 0 && g == 0 && b == 0) {
					image.setPixel(i, j,1);
				}
				else
				{
					image.setPixel(i, j,0);
				}
			}
			

			counting++;
			if (counting == coile)
				counting = 0;
		}
	}

	

	s << "f:/softcomputing/noise/" <<"noise_znak"<<c<<"_" <<pr << ".png";
	ss = s.str();
	s.str("");
	image.save(ss.c_str());

	s << "f:/softcomputing/noise/noise_znak"<<c<<"_" << pr << ".png";
	ss = s.str();
	s.str("");


	image.load(ss.c_str());
		
		
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {

				col = QColor::fromRgb(image.pixel(i, j));
				col.getRgb(&r, &g, &b, &p);
				if (r == 0 && g == 0 && b == 0) {
					proba[i][j] = 1;
				}
				else
				{
					proba[i][j] = -1;
				}
			}
		}

	std::cout << std::endl;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (proba[i][j] == 1)
				std::cout << " " << proba[i][j] << " ";
			else
				std::cout <<proba[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

void ImagePreProcessing::mudFunction(string fullpath,int c, int tryb)
{
	stringstream s;
	string ss;

	s << fullpath << c << ".png";
	ss = s.str();
	s.str("");
	QImage image;
	image.load(ss.c_str());

	switch(tryb)
	{
	case 1:
		coverImage(image, 8, 8);
		break;
	case 2:
		coverImage(image, 16, 8);
		break;
	case 3:
		coverImage(image, 8, 16);
		break;
	case 4:
		coverImage(image, 16, 16);
		break;
	default:
		break;
	}

	s << "f:/softcomputing/mud/" << "mud_znak" << c << "_w_trybie"<<tryb << ".png";
	ss = s.str();
	s.str("");
	image.save(ss.c_str());

	s << "f:/softcomputing/mud/mud_znak" << c << "_w_trybie" <<tryb << ".png";
	ss = s.str();
	s.str("");


	image.load(ss.c_str());

	QColor col;
	vector<vector<int>> proba(16, vector<int>(16));
	int r, g, b, p;

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {

			col = QColor::fromRgb(image.pixel(i, j));
			col.getRgb(&r, &g, &b, &p);
			if (r == 0 && g == 0 && b == 0) {
				proba[i][j] = 1;
			}
			else
			{
				proba[i][j] = -1;
			}
		}
	}

	std::cout << std::endl;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (proba[i][j] == 1)
				std::cout << " " << proba[i][j] << " ";
			else
				std::cout << proba[i][j] << " ";
		}
		std::cout << std::endl;
	}

}


