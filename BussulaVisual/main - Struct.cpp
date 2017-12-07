#include "opencv2/opencv.hpp"

using namespace cv;

cv::Mat lerImage()
{
	cv::Mat image;
	image = cv::imread("campo03.jpg", CV_LOAD_IMAGE_COLOR);

	return image;
}

//struct pixel {
//	int red;
//	int green;
//	int blue;
//	int row;
//	int col;
//	struct pixel *prox;
//};

typedef struct pixel {
	int red;
	int green;
	int blue;
	int row;
	int col;
	struct pixel *prox;
}Pixel;

Pixel *inserePixel(int r, int g, int b, int row, int col, Pixel *lista)
{
	pixel *nova, *p;
	nova = (pixel *)malloc(sizeof(pixel));
	nova->red = r;
	nova->blue = b;
	nova->green = g;
	nova->row = row;
	nova->col = col;
	nova->prox = NULL;

	if (!lista)
	{
		return nova;
	}

	p = lista;

	while (p->prox)
	{
		p = p->prox;
	}

	p->prox = nova;

	return lista;

	/*if (p != NULL)
	{
		p->prox = inserePixel(r, g, b, row, col, p->prox);
		return p;
	}

	Pixel *nova;
	nova = (Pixel*)malloc(sizeof(Pixel));
	nova->red = r;
	nova->green = g;
	nova->blue = b;
	nova->prox = NULL;*/
	//p->prox = nova;

	//return nova;
}

void imprimaPixel(Pixel *ini) {
	/*pixel *p;
	for (p = ini; p != NULL; p = p->prox)
	{
		printf("Linha: %d\n", p->row);
		printf("Coluna:%d\n", p->col);
		printf("\n");
	}*/
	if (!ini)
		printf("\nLista Vazia!\n");
	while (ini)
	{
		printf("[%i]\n", ini->row);
		printf("[%i]\n", ini->col);
		printf("\n\n");
		ini = ini->prox;
	}
}

int main(int, char)
{
	cv::Mat image;
	cv::Mat *img;
	/*cv::Mat aux;
	cv::Mat hsv;
	cv::Mat yuv;
	cv::Mat yuvI420;
	cv::Mat yuvIYUV;
	cv::Mat yuvYV12;*/
	int vet[2] = {0,256};
	image = lerImage();
	cv::calcHist(img, 0, NULL, vet, 0, 256, 256, 256, true, false);
	Pixel *primeira;
	Pixel p;
	primeira = (Pixel*)malloc(sizeof(Pixel));
	//p = (Pixel*)malloc(sizeof(Pixel));

	bool flag = true;
	//cores mais frequentes e histograma
	//transição de cores - segmentar o espaçode cores em um grupo finito de cores(k-means)
	for (int i = 0; i < image.rows; i++)
	{
		for (int x = 0; x < 10; x++)
		{
			for (int j = x; j < image.cols; j = j + 20)
			{
				Vec3b bgrPixel = image.at<Vec3b>(i, j);

				bgrPixel.val[0] = 0; // B
				bgrPixel.val[1] = 0; // G
				bgrPixel.val[2] = 0; // R

				/*if (flag)
				{
					primeira->red = (int)bgrPixel.val[2];
					primeira->green = (int)bgrPixel.val[1];
					primeira->blue = (int)bgrPixel.val[0];
					primeira->row = i;
					primeira->col = j;
					primeira->prox = NULL;

					p = *primeira;

					flag = !flag;
				}
				else
				{
					primeira = inserePixel(bgrPixel.val[2], bgrPixel.val[1], bgrPixel.val[0], i, j, primeira);
				}
*/
				image.at<Vec3b>(i, j) = bgrPixel;



				//if (image.at<uchar>(j, i) < 100)
				//image.at<uchar>(i, j) = 0;

				/*else if (image.at<uchar>(j, i) > 200)
				image.at<uchar>(j, i) = 255;*/
			}
		}
	}

	//imprimaPixel(primeira);

	cv::imshow("aaaaaaaaaaa", image);

	//cv::namedWindow("janela", CV_WINDOW_AUTOSIZE);
	//cv::imshow("janela", image);

	//cv::cvtColor(image, hsv, CV_RGB2HSV);//=
	//cv::cvtColor(image, aux, CV_BGR2HSV);//=
	/*cv::cvtColor(image, yuvI420, CV_BGR2YUV_I420);
	cv::cvtColor(image, yuv, CV_BGR2YUV);
	cv::cvtColor(image, yuvIYUV, CV_BGR2YUV_IYUV);
	cv::cvtColor(image, yuvYV12, CV_BGR2YUV_YV12);*/

	//cv::imshow("rgb_to_hsv", hsv);// =
	//cv::imshow("bgr_to_hsv", aux);// =
	/*cv::imshow("yuv", yuv);
	cv::imshow("yuvI420", yuvI420);
	cv::imshow("yuvIYUV", yuvIYUV);
	cv::imshow("yuvYV12", yuvYV12);*/



	cv::waitKey(0);

	return 0;
}