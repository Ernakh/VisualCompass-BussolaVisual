#include "opencv2/opencv.hpp"
#include "MyPixelInfo.h"
#include <list>
#include <iostream>
#include <fstream>
#include <stdlib.h>
//#include <cstdlib>
//#include <cstdio>

using namespace cv;


#define imagemColuna 24272
#define imagemLinhas 1918

#define countColunas 2500

#define imagemNewColuna 1918
#define imagemNewLinhas 1079

#define countNewColunas 121

//#define imagemColuna 2435
//#define imagemLinhas 185
//
//#define countColunas 121
//
//#define imagemNewColuna 343
//#define imagemNewLinhas 184

//#define countNewColunas 17

cv::Mat lerImage()
{
	cv::Mat image;
	image = cv::imread("360_2.jpg", CV_LOAD_IMAGE_COLOR);
	//image = cv::imread("_360.jpg", CV_LOAD_IMAGE_COLOR);

	//se iamgme grande demasiadamente. pq??
	//cv::flip(image, image, 1);
	cv::flip(image, image, -1);
	
	return image;
}

cv::Mat lerImage2()
{
	cv::Mat image;
	image = cv::imread("lab (1).jpg", CV_LOAD_IMAGE_COLOR);
	//image = cv::imread("_360_new.jpg", CV_LOAD_IMAGE_COLOR);

	return image;
}

void colorReduce(cv::Mat& image, int div = 128)
{
	int nl = image.rows;
	int nc = image.cols * image.channels();

	for (int j = 0; j < nl; j++)
	{
		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++)
		{
			data[i] = data[i] / div * div + div / 2;
		}
	}

	/*
	CORES Remanescentes:

	amarelo 192 192 64
	cinza 64 64 64
	vermelho 192 64 64
	azul 64 64 192
	verde 64 192 64
	rosa 192 64 192
	branco 192 192 192
	ciano 64 192 192

	*/
}

////parece que só funciona com espaço
//std::vector<std::string> split(std::string str, char delimiter = ' ')
//{
//	std::vector<std::string> ret;
//
//	if ((str.find(delimiter) == std::string::npos) && (str.find_first_not_of(delimiter) == std::string::npos))
//		throw nullptr;
//	else if (str.find(delimiter) == std::string::npos)
//		ret.push_back(str);
//	else if (str.find_first_not_of(delimiter) == std::string::npos)
//		ret.push_back(std::string(""));
//	else
//	{
//		unsigned i = 0;
//		std::string strstack;
//
//		while (str[0] == delimiter)
//		{
//			str.erase(0, 1);
//		}
//
//		reverse(str.begin(), str.end());
//
//		while (str[0] == delimiter)
//		{
//			str.erase(0, 1);
//		}
//
//		reverse(str.begin(), str.end());
//
//		while (!str.empty())
//		{
//			ret.push_back(str.substr(i, str.find(delimiter)));
//
//			str.erase(0, str.find(delimiter));
//
//			while (str[0] == delimiter)
//			{
//				str.erase(0, 1);
//			}
//		}
//	}
//
//	return ret;
//}

std::vector<std::string> split(std::string str, char delimiter = ' ')
{
	std::vector<std::string> ret;

	if (str.empty())
	{
		ret.push_back(std::string(""));
		return ret;
	}

	unsigned i = 0;
	std::string strstack;

	while (!(str.empty()) && (str[0] == delimiter))
	{
		str.erase(0, 1);
	}

	reverse(str.begin(), str.end());

	while (!(str.empty()) && (str[0] == delimiter))
	{
		str.erase(0, 1);
	}

	reverse(str.begin(), str.end());

	while (!str.empty())
	{
		ret.push_back(str.substr(i, str.find(delimiter)));
		str.erase(0, str.find(delimiter));

		while (!(str.empty()) && (str[0] == delimiter))
		{
			str.erase(0, 1);
		}
	}

	return ret;
}

cv::Mat ProcessaImagem()
{
	cv::Mat image;
	cv::Mat hsv;
	//int vet[2] = {0,256};
	image = lerImage();

	int erosion_size = 2;
	Mat element = getStructuringElement(cv::MORPH_OPEN,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));

	//erode(image, image, element);

	//cv::dilate(image, image, (5, 5), Point(-1, -1), 1, 1, 1);
	//cv::morphologyEx(image, image, MORPH_OPEN, (15, 15));

	cv::cvtColor(image, hsv, CV_BGR2HSV);

	cv::Mat aux = hsv.clone();

	Mat element2 = getStructuringElement(cv::MORPH_OPEN,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));

	//Apply erosion or dilation on the image
	//erode(aux, aux, element2);
	//dilate(aux, aux, element);

	colorReduce(aux);

	return aux;
}

cv::Mat ProcessaImagem2()
{
	cv::Mat image;
	cv::Mat hsv;
	//int vet[2] = {0,256};
	image = lerImage2();

	int erosion_size = 2;
	Mat element = getStructuringElement(cv::MORPH_OPEN,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));

	//erode(image, image, element);

	//cv::dilate(image, image, (5, 5), Point(-1, -1), 1, 1, 1);
	//cv::morphologyEx(image, image, MORPH_OPEN, (15, 15));

	cv::cvtColor(image, hsv, CV_BGR2HSV);

	cv::Mat aux = hsv.clone();

	Mat element2 = getStructuringElement(cv::MORPH_OPEN,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));

	//Apply erosion or dilation on the image
	//erode(aux, aux, element2);
	//dilate(aux, aux, element);

	colorReduce(aux);

	return aux;
}

struct A
{
	int Matriz[8][8];
};

struct Correlacoes
{
	int correlacao;
	int colBuss;
	int colNew;
};

struct CorrelacoesSoma
{
	int soma;
	int de;
	int ate;
	int colunaBussola;
	int colunaNew;
};

struct CossineOrder
{
	int bussola;
	int ColNew;
	double valor;
};

bool sort_by_soma(const CorrelacoesSoma & cm, const CorrelacoesSoma & cm2)
{
	return cm.soma < cm2.soma;
}

int main(int, char)
{
	//não sei pq nao consigo adicioanr uam matriz em uma std::list
	/*std::list<int[8][8]> MatrizesNew;
	std::list<int[8][8]> MatrizesBussola;*/
	std::list<A> MatrizesBussola;
	std::list<A> MatrizesNew;

	int op;

	do
	{
		printf("\n =================================================\t\t\a");
		printf("\n\n 1 - Criar arquivos - CALIBRAR");
		printf("\n\n 2 - Identificar Trocas de cores (arquivo txt)");
		printf("\n\n 3 - Comparar novo frame (foto)");
		printf("\n\n 4 - Repete passo 1 e 2 para uma nova imagem");
		printf("\n\n 5 - Gera Histograma de troca de cores");
		printf("\n\n 6 - Repete passo 5 para novo frame");
		printf("\n\n 7 - Gera Matrizes para o calculo de similaridade");
		printf("\n\n 8 - Calculo similaridade - cosine_similarity -1 to 1");
		printf("\n\n 9 - Calculo similaridade - manhathan");
		printf("\n\n 10 - Calculo similaridade - Jaccard 0 to 1");
		printf("\n\n 11 - Calculo similaridade - Euclideana");
		printf("\n\n 12 - Calculo similaridade - ...");
		printf("\n\n 13 - Calculo similaridade - Correlação Cruzada - incompleta");
		printf("\n\n 14 - Calculo similaridade - Correlação Cruzada");
		printf("\n\n 99 - transforma imagem - não importante, nao usar, apenas teste!");
		printf("\n\n 0 - SAIR");
		printf("\n\n\t\t Introduza opçao:");
		scanf("%d", &op);

		if (op == 1)
		{
			//melhorar no futuro, removendo os laços duplicados
			system("cls");
			printf("processando, aguarde...\n\n\n");

			cv::Mat aux = ProcessaImagem();

			//cores mais frequentes - histograma
			//transição de cores - segmentar o espaçode cores em um grupo finito de cores(k-means)
			/*	std::list<MyPixelInfo> lista;

				int r[256];
				int g[256];
				int b[256];

				for (int i = 0; i < 256; i++)
				{
				r[i] = 0;
				g[i] = 0;
				b[i] = 0;
				}*/

			for (int i = 0; i < aux.rows; i++)
			{
				for (int x = 0; x < 10; x++)
				{
					for (int j = x; j < aux.cols; j = j + 20)
					{
						Vec3b bgrPixel = aux.at<Vec3b>(i, j);

						char coluna[10];
						_snprintf(coluna, 10, "%d.txt", j);

						std::ofstream myfile;
						myfile.open(coluna, std::ios_base::app);
						/*myfile << "linha ";
						myfile << i;
						myfile << "\n";*/
						//myfile << "b\n";
						myfile << (int)bgrPixel(0);
						myfile << " ";
						//myfile << "g\n";
						myfile << (int)bgrPixel(1);
						myfile << " ";
						//myfile << "r\n";
						myfile << (int)bgrPixel(2);
						myfile << "\n";
						//myfile << "\n";
						myfile.close();

						//remove("arquivo.txt");

						//contando cada ocorrencia da cor
						/*b[bgrPixel.val[0]]++;
						g[bgrPixel.val[1]]++;
						r[bgrPixel.val[2]]++;*/

						//bgrPixel.val[0] = 100; // B
						//bgrPixel.val[1] = 100; // G
						//bgrPixel.val[2] = 100; // R

						/*MyPixelInfo *pixel = new MyPixelInfo();

						pixel->red = (int)bgrPixel.val[2];
						pixel->green = (int)bgrPixel.val[1];
						pixel->blue = (int)bgrPixel.val[0];
						pixel->row = i;
						pixel->col = j;

						aux.at<Vec3b>(i, j) = bgrPixel;

						lista.push_back(*pixel);*/

						//if (image.at<uchar>(j, i) < 100)


						/*else if (image.at<uchar>(j, i) > 200)
						image.at<uchar>(j, i) = 255;*/
					}
				}
			}

			for (int i = 0; i < aux.rows; i++)
			{
				for (int x = 0; x < 10; x++)
				{
					for (int j = x; j < aux.cols; j = j + 20)
					{
						Vec3b bgrPixel = aux.at<Vec3b>(i, j);

						if (i == 0 && j % 10 == 0)
						{
							cv::rectangle(aux, cvRect(j, i, 10, aux.rows), CvScalar(0, 128, 255), 1, 1, 0);
						}

						try
						{
							if (bgrPixel.val[0] < 200)
								bgrPixel.val[0] = bgrPixel.val[0] + 50; // B
							if (bgrPixel.val[1] < 200)
								bgrPixel.val[1] = bgrPixel.val[1] + 50; // G
							if (bgrPixel.val[2] < 200)
								bgrPixel.val[2] = bgrPixel.val[2] + 50; // R

							aux.at<Vec3b>(i, j) = bgrPixel;
						}
						catch (int e)
						{
							continue;
						}
					}
				}
			}

			printf("\a");

			cv::imshow("Imagem Final", aux);
			cv::waitKey(0);

			system("cls");
		}
		else if (op == 2)
		{
			//lendo um arquivo com os dados dos pixels e gerando um novo com as informações das trocas de cores
			system("cls");
			printf("Identificando Trocas de cores (arquivo txt)...\n\n");

			cv::Mat image;

			image = lerImage();

			for (int i = 0; i < image.cols; i++)
			{
				char arquivo[10];
				_snprintf(arquivo, 10, "%d.txt", i);

				std::ifstream file;

				if (!file)
					continue;

				file.open(arquivo);

				int cont = 0;

				if (file.is_open())
				{
					//char output[100];
					std::string previousLine;
					std::string line;

					std::getline(file, previousLine);

					int linha = 0;

					while (!file.eof())
					{
						std::getline(file, line);

						/*std::cout << "\n\n";
						std::cout << line;
						std::cout << "\n\n";*/

						if (line == previousLine)
						{
							linha++;
							continue;
						}

						//armazenar o que teve de mudança de cor

						char arquivoNovo[19];
						_snprintf(arquivoNovo, 19, "%d trocas.txt", i);

						std::ofstream newfile;
						newfile.open(arquivoNovo, std::ios_base::app);

						newfile << previousLine;
						newfile << " para ";
						newfile << line;
						newfile << " na linha(pixel) ";
						newfile << linha;
						newfile << "\n";
						newfile.close();

						previousLine = line;

						//std::vector<std::string> split_vector = split(line);
						//for (int x = 0; x < split_vector.size(); x++)
						//{
						//	std::cout << split_vector[x];
						//	std::cout << "\n";

						//	//fazer o resto
						//}

						linha++;
					}
				}

				cont++;

				file.close();

				//remove(arquivo);//descomentar no futuro
			}

			/*for (std::list<MyPixelInfo>::iterator it = lista.begin(); it != lista.end(); it++)
			{
			printf("Linha: %d\n", it->row);
			printf("Coluna:%d\n", it->col);
			printf("Vermelho:%d\n", it->red);
			printf("Verde:%d\n", it->green);
			printf("Azul:%d\n", it->blue);
			printf("\n");
			}*/

			//cv::namedWindow("janela", CV_WINDOW_AUTOSIZE);
			//cv::imshow("janela", image);

			//cv::imshow("hsv", hsv);
			//cv::imshow("auxiliar", aux);

			//cv::waitKey(0);

			system("cls");
			printf("\a");
		}
		else if (op == 3)
		{
			//refazer esta etapa do zero no futuro
			system("cls");

			std::list<std::string> i_comMelhorJ;

			for (int i = 0; i < imagemColuna; i++)
			{
				char arquivo[26];
				_snprintf(arquivo, 26, "new %d trocas.txt", i);

				std::ifstream frameAnalisar;

				if (!frameAnalisar)
					continue;

				frameAnalisar.open(arquivo);

				if (frameAnalisar.is_open())
				{
					std::string linhaFrame;

					while (!frameAnalisar.eof())
					{
						std::getline(frameAnalisar, linhaFrame);

						//estou contabilizando as trocas iguais, melhorar para a ordem ser considerada, ignorando se iniciou da troca correta 
						//(imagina q tem uma nova cor no inicio, adicionando apenas uma nova troca no inicio
						int acertosAnterior = 0;
						int melhorJ = 0;

						for (int j = 0; j < imagemColuna; j++)
						{
							std::ifstream arquivoBussola;

							char nomeArquivoBussola[26];
							_snprintf(nomeArquivoBussola, 26, "%d trocas.txt", j);

							if (!arquivoBussola)
								continue;

							arquivoBussola.open(nomeArquivoBussola);

							std::string linhaBussola;

							int acertos = 0;
							int erros = 0;

							if (arquivoBussola.is_open())
							{
								while (!arquivoBussola.eof())
								{
									std::getline(arquivoBussola, linhaBussola);

									std::vector<std::string> vetorLinhaBussola = split(linhaBussola, 'n');
									std::vector<std::string> vetorLinhaAnalisar = split(linhaFrame, 'n');

									if (vetorLinhaBussola[0] == vetorLinhaAnalisar[0])
									{
										acertos++;
									}
									else
									{
										erros++;
									}
								}
							}
							else
							{
								continue;
							}

							if (erros == 0)
							{
								acertosAnterior = 100;
								melhorJ = j;
								break;
							}

							if (acertos > erros)
							{
								acertosAnterior = acertos;
								melhorJ = j;
							}
							else if (acertos >= 4)
							{
								acertosAnterior = acertos;
								melhorJ = j;
							}
						}

						/*if (acertosAnterior == 100)
						{*/
						char paraLista[13];
						_snprintf(paraLista, 13, "%d - %d", i, melhorJ);

						/*std::stringstream ss;
						std::string aux;

						ss << paraLista;
						ss >> aux;*/

						//i_comMelhorJ.push_back(aux);
						i_comMelhorJ.push_back(std::string(paraLista));
						break;
						/*}
						else
						{
						char paraLista[12];
						_snprintf(paraLista, 12, "%d - %d", i, melhorJ);

						i_comMelhorJ.push_back(std::string(paraLista));
						}*/
					}
				}
			}

			for (std::list<std::string>::iterator it = i_comMelhorJ.begin(); it != i_comMelhorJ.end(); ++it)
			{
				std::cout << "\n" << *it;
			}

			system("cls");
			printf("\a");
		}
		else if (op == 4)
		{
			system("cls");
			printf("processando novo frame \n");

			cv::Mat newImage = ProcessaImagem2();

			for (int i = 0; i < newImage.rows; i++)
			{
				for (int x = 0; x < 10; x++)
				{
					for (int j = x; j < newImage.cols; j = j + 20)
					{
						Vec3b bgrPixel = newImage.at<Vec3b>(i, j);

						char coluna[21];
						_snprintf(coluna, 21, "new %d.txt", j);

						std::ofstream myfile;
						myfile.open(coluna, std::ios_base::app);

						myfile << (int)bgrPixel(0);
						myfile << " ";
						myfile << (int)bgrPixel(1);
						myfile << " ";
						myfile << (int)bgrPixel(2);
						myfile << "\n";
						myfile.close();
					}
				}
			}

			//destacar colunas e desenhar quadrado na area de interesse
			for (int i = 0; i < newImage.rows; i++)
			{
				for (int x = 0; x < 10; x++)
				{
					for (int j = x; j < newImage.cols; j = j + 20)
					{
						Vec3b bgrPixel = newImage.at<Vec3b>(i, j);

						if (i == 0 && j % 10 == 0)
						{
							cv::rectangle(newImage, cvRect(j, i, 10, newImage.rows), CvScalar(0, 128, 255), 1, 1, 0);
						}

						try
						{
							if (bgrPixel.val[0] < 200)
								bgrPixel.val[0] = bgrPixel.val[0] + 50; // B
							if (bgrPixel.val[1] < 200)
								bgrPixel.val[1] = bgrPixel.val[1] + 50; // G
							if (bgrPixel.val[2] < 200)
								bgrPixel.val[2] = bgrPixel.val[2] + 50; // R

							newImage.at<Vec3b>(i, j) = bgrPixel;
						}
						catch (int e)
						{
							continue;
						}
					}
				}
			}

			printf("\a");

			cv::imshow("Imagem para comparação", newImage);
			cv::waitKey(0);

			for (int i = 0; i < newImage.cols; i++)
			{
				char arquivo[26];
				_snprintf(arquivo, 26, "new %d.txt", i);

				std::ifstream file;

				if (!file)
					continue;

				file.open(arquivo);

				int cont = 0;

				if (file.is_open())
				{
					std::string previousLine;
					std::string line;

					std::getline(file, previousLine);

					int linha = 0;

					while (!file.eof())
					{
						std::getline(file, line);

						if (line == previousLine)
						{
							linha++;
							continue;
						}

						char arquivoNovo[26];
						_snprintf(arquivoNovo, 26, "new %d trocas.txt", i);

						std::ofstream newfile;
						newfile.open(arquivoNovo, std::ios_base::app);

						newfile << previousLine;
						newfile << " para ";
						newfile << line;
						newfile << " na linha(pixel) ";
						newfile << linha;
						newfile << "\n";
						newfile.close();

						previousLine = line;

						linha++;
					}
				}

				cont++;
				file.close();

				//remove(arquivo);//descomentar no futuro
			}

			system("cls");
			printf("\a");
		}
		else if (op == 5)
		{
			system("cls");
			printf("\n\nProcessando...\n\n");

			std::list<MyPixelInfo> lista;

			int columnName = 0;

			for (int i = 0; i < imagemColuna; i++)
			{
				char arquivo[26];
				_snprintf(arquivo, 26, "%d trocas.txt", i);

				std::ifstream file(arquivo);

				if (!file)
				{
					char arquivoNovo[26];
					_snprintf(arquivoNovo, 26, "histograma %d.txt", columnName);

					std::ofstream newfile;
					newfile.open(arquivoNovo, std::ios_base::app);

					for (std::list<MyPixelInfo>::iterator it = lista.begin(); it != lista.end(); ++it)
					{
						newfile << it->origin_red;
						newfile << " ";
						newfile << it->origin_green;
						newfile << " ";
						newfile << it->origin_blue;
						newfile << " para ";
						newfile << it->destiny_red;
						newfile << " ";
						newfile << it->destiny_green;
						newfile << " ";
						newfile << it->destiny_blue;
						newfile << " : ";
						newfile << it->count;
						newfile << "\n";
					}

					newfile.close();

					i += 9;

					columnName += 1;

					lista.clear();

					file.close();

					continue;
				}

				//file.open(arquivo);

				if (file.is_open())
				{
					while (!file.eof())
					{
						std::string line;
						std::getline(file, line);

						std::vector<std::string> splitted_vector = split(line);

						if (splitted_vector.size() < 8)
							break;

						MyPixelInfo mpi;
						mpi.origin_red = std::stoi(splitted_vector[0]);
						mpi.origin_green = std::stoi(splitted_vector[1]);
						mpi.origin_blue = std::stoi(splitted_vector[2]);
						mpi.destiny_red = std::stoi(splitted_vector[4]);
						mpi.destiny_green = std::stoi(splitted_vector[5]);
						mpi.destiny_blue = std::stoi(splitted_vector[6]);
						mpi.count = 1;

						if (lista.empty())
						{
							lista.push_back(mpi);
						}
						else
						{
							bool found = false;

							for (std::list<MyPixelInfo>::iterator it = lista.begin(); it != lista.end(); ++it)
							{
								if (mpi.origin_red == it->origin_red &&
									mpi.origin_green == it->origin_green &&
									mpi.origin_blue == it->origin_blue &&
									mpi.destiny_red == it->destiny_red &&
									mpi.destiny_green == it->destiny_green &&
									mpi.destiny_blue == it->destiny_blue)
								{
									found = true;

									it->count = it->count + 1;

									break;
								}
							}

							if (!found)
							{
								lista.push_back(mpi);
							}
						}
					}
				}
			}

			system("cls");
			printf("\a");
		}
		else if (op == 6)
		{
			system("cls");
			printf("\n\nprocessando...\n\n");

			std::list<MyPixelInfo> lista;

			int columnName = 0;

			for (int i = 0; i < imagemNewColuna; i++)
			{
				char arquivo[26];
				_snprintf(arquivo, 26, "new %d trocas.txt", i);

				std::ifstream file(arquivo);

				if (!file)
				{
					char arquivoNovo[26];
					_snprintf(arquivoNovo, 26, "new histograma %d.txt", columnName);

					std::ofstream newfile;
					newfile.open(arquivoNovo, std::ios_base::app);

					for (std::list<MyPixelInfo>::iterator it = lista.begin(); it != lista.end(); ++it)
					{
						newfile << it->origin_red;
						newfile << " ";
						newfile << it->origin_green;
						newfile << " ";
						newfile << it->origin_blue;
						newfile << " para ";
						newfile << it->destiny_red;
						newfile << " ";
						newfile << it->destiny_green;
						newfile << " ";
						newfile << it->destiny_blue;
						newfile << " : ";
						newfile << it->count;
						newfile << "\n";
					}

					newfile.close();

					i += 9;

					columnName += 1;

					lista.clear();

					file.close();

					continue;
				}

				//file.open(arquivo);

				if (file.is_open())
				{
					while (!file.eof())
					{
						std::string line;
						std::getline(file, line);

						std::vector<std::string> splitted_vector = split(line);

						if (splitted_vector.size() < 8)
							break;

						MyPixelInfo mpi;
						mpi.origin_red = std::stoi(splitted_vector[0]);
						mpi.origin_green = std::stoi(splitted_vector[1]);
						mpi.origin_blue = std::stoi(splitted_vector[2]);
						mpi.destiny_red = std::stoi(splitted_vector[4]);
						mpi.destiny_green = std::stoi(splitted_vector[5]);
						mpi.destiny_blue = std::stoi(splitted_vector[6]);
						mpi.count = 1;

						if (lista.empty())
						{
							lista.push_back(mpi);
						}
						else
						{
							bool found = false;

							for (std::list<MyPixelInfo>::iterator it = lista.begin(); it != lista.end(); ++it)
							{
								if (mpi.origin_red == it->origin_red &&
									mpi.origin_green == it->origin_green &&
									mpi.origin_blue == it->origin_blue &&
									mpi.destiny_red == it->destiny_red &&
									mpi.destiny_green == it->destiny_green &&
									mpi.destiny_blue == it->destiny_blue)
								{
									found = true;

									it->count = it->count + 1;

									break;
								}
							}

							if (!found)
							{
								lista.push_back(mpi);
							}
						}
					}
				}
			}

			system("cls");
			printf("\a");
		}
		else if (op == 7)
		{
			system("cls");
			printf("\n\nGerando matrizes.... \n\n");

			for (int i = 0; i < countColunas; i++)
			{
				char arquivo[26];
				_snprintf(arquivo, 26, "histograma %d.txt", i);

				std::ifstream file(arquivo);

				if (!file)
				{
					continue;
				}

				if (file.is_open())
				{
					/*
					0 - amarelo - 192 192 64
					1 - cinza - 64 64 64
					2 - vermelho - 192 64 64
					3 - azul - 64 64 192
					4 - verde - 64 192 64
					5 - rosa - 192 64 192
					6 - branco - 192 192 192
					7 - ciano - 64 192 192
					*/

					//adicionar todas as matrizes em uma lista? 1 matriz por arquivo
					//int MatrizBussola[8][8];
					A MatrizBussola;

					for (int x = 0; x < 8; x++)
					{
						for (int j = 0; j < 8; j++)
						{
							MatrizBussola.Matriz[x][j] = 0;
						}
					}

					while (!file.eof())
					{
						std::string line;
						std::getline(file, line);

						std::vector<std::string> splitted_vector = split(line);

						//amarelo para
						if (splitted_vector[0] == "192" && splitted_vector[1] == "192" && splitted_vector[2] == "64")
						{
							//cinza
							if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[0][1] = std::stoi(splitted_vector[8]);
							}
							//vermelho
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[0][2] = std::stoi(splitted_vector[8]);
							}
							//azul
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[0][3] = std::stoi(splitted_vector[8]);
							}
							//verde
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[0][4] = std::stoi(splitted_vector[8]);
							}
							//rosa
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[0][5] = std::stoi(splitted_vector[8]);
							}
							//branco
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[0][6] = std::stoi(splitted_vector[8]);
							}
							//ciano
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[0][7] = std::stoi(splitted_vector[8]);
							}
						}
						//cinza para
						else if (splitted_vector[0] == "64" && splitted_vector[1] == "64" && splitted_vector[2] == "64")
						{
							//amarelo
							if (splitted_vector[0] == "192" && splitted_vector[1] == "192" && splitted_vector[2] == "64")
							{
								MatrizBussola.Matriz[1][0] = std::stoi(splitted_vector[8]);
							}
							//vermelho
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[1][2] = std::stoi(splitted_vector[8]);
							}
							//azul
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[1][3] = std::stoi(splitted_vector[8]);
							}
							//verde
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[1][4] = std::stoi(splitted_vector[8]);
							}
							//rosa
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[1][5] = std::stoi(splitted_vector[8]);
							}
							//branco
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[1][6] = std::stoi(splitted_vector[8]);
							}
							//ciano
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[1][7] = std::stoi(splitted_vector[8]);
							}
						}
						//vermelho para
						else if (splitted_vector[0] == "192" && splitted_vector[1] == "64" && splitted_vector[2] == "64")
						{
							//amarelo
							if (splitted_vector[0] == "192" && splitted_vector[1] == "192" && splitted_vector[2] == "64")
							{
								MatrizBussola.Matriz[2][0] = std::stoi(splitted_vector[8]);
							}
							//cinza
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[2][1] = std::stoi(splitted_vector[8]);
							}
							//azul
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[2][3] = std::stoi(splitted_vector[8]);
							}
							//verde
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[2][4] = std::stoi(splitted_vector[8]);
							}
							//rosa
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[2][5] = std::stoi(splitted_vector[8]);
							}
							//branco
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[2][6] = std::stoi(splitted_vector[8]);
							}
							//ciano
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[2][7] = std::stoi(splitted_vector[8]);
							}
						}
						//azul para
						else if (splitted_vector[0] == "64" && splitted_vector[1] == "64" && splitted_vector[2] == "192")
						{
							//amarelo
							if (splitted_vector[0] == "192" && splitted_vector[1] == "192" && splitted_vector[2] == "64")
							{
								MatrizBussola.Matriz[3][0] = std::stoi(splitted_vector[8]);
							}
							//cinza
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[3][1] = std::stoi(splitted_vector[8]);
							}
							//vermelho
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[3][2] = std::stoi(splitted_vector[8]);
							}
							//verde
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[3][4] = std::stoi(splitted_vector[8]);
							}
							//rosa
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[3][5] = std::stoi(splitted_vector[8]);
							}
							//branco
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[3][6] = std::stoi(splitted_vector[8]);
							}
							//ciano
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[3][7] = std::stoi(splitted_vector[8]);
							}
						}
						//verde para
						else if (splitted_vector[0] == "64" && splitted_vector[1] == "192" && splitted_vector[2] == "64")
						{
							//amarelo
							if (splitted_vector[0] == "192" && splitted_vector[1] == "192" && splitted_vector[2] == "64")
							{
								MatrizBussola.Matriz[4][0] = std::stoi(splitted_vector[8]);
							}
							//cinza
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[4][1] = std::stoi(splitted_vector[8]);
							}
							//vermelho
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[4][2] = std::stoi(splitted_vector[8]);
							}
							//azul
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[4][3] = std::stoi(splitted_vector[8]);
							}
							//rosa
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[4][5] = std::stoi(splitted_vector[8]);
							}
							//branco
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[4][6] = std::stoi(splitted_vector[8]);
							}
							//ciano
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[4][7] = std::stoi(splitted_vector[8]);
							}
						}
						//rosa para
						else if (splitted_vector[0] == "192" && splitted_vector[1] == "64" && splitted_vector[2] == "192")
						{
							//amarelo
							if (splitted_vector[0] == "192" && splitted_vector[1] == "192" && splitted_vector[2] == "64")
							{
								MatrizBussola.Matriz[5][0] = std::stoi(splitted_vector[8]);
							}
							//cinza
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[5][1] = std::stoi(splitted_vector[8]);
							}
							//vermelho
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[5][2] = std::stoi(splitted_vector[8]);
							}
							//azul
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[5][3] = std::stoi(splitted_vector[8]);
							}
							//verde
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[5][4] = std::stoi(splitted_vector[8]);
							}
							//branco
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[5][6] = std::stoi(splitted_vector[8]);
							}
							//ciano
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[5][7] = std::stoi(splitted_vector[8]);
							}
						}
						//branco para
						else if (splitted_vector[0] == "192" && splitted_vector[1] == "192" && splitted_vector[2] == "192")
						{
							//amarelo
							if (splitted_vector[0] == "192" && splitted_vector[1] == "192" && splitted_vector[2] == "64")
							{
								MatrizBussola.Matriz[6][0] = std::stoi(splitted_vector[8]);
							}
							//cinza
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[6][1] = std::stoi(splitted_vector[8]);
							}
							//vermelho
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[6][2] = std::stoi(splitted_vector[8]);
							}
							//azul
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[6][3] = std::stoi(splitted_vector[8]);
							}
							//verde
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[6][4] = std::stoi(splitted_vector[8]);
							}
							//rosa
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[6][5] = std::stoi(splitted_vector[8]);
							}
							//ciano
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[6][7] = std::stoi(splitted_vector[8]);
							}
						}
						//ciano para
						else if (splitted_vector[0] == "64" && splitted_vector[1] == "192" && splitted_vector[2] == "192")
						{
							//amarelo
							if (splitted_vector[0] == "192" && splitted_vector[1] == "192" && splitted_vector[2] == "64")
							{
								MatrizBussola.Matriz[7][0] = std::stoi(splitted_vector[8]);
							}
							//cinza
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[7][1] = std::stoi(splitted_vector[8]);
							}
							//vermelho
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[7][2] = std::stoi(splitted_vector[8]);
							}
							//azul
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[7][3] = std::stoi(splitted_vector[8]);
							}
							//verde
							else if (splitted_vector[4] == "64" && splitted_vector[5] == "192" && splitted_vector[6] == "64")
							{
								MatrizBussola.Matriz[7][4] = std::stoi(splitted_vector[8]);
							}
							//rosa
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "64" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[7][5] = std::stoi(splitted_vector[8]);
							}
							//branco
							else if (splitted_vector[4] == "192" && splitted_vector[5] == "192" && splitted_vector[6] == "192")
							{
								MatrizBussola.Matriz[7][6] = std::stoi(splitted_vector[8]);
							}
						}
					}

					printf("===== %d =====\n", i);

					for (int x = 0; x < 8; x++)
					{
						for (int j = 0; j < 8; j++)
						{
							printf("[%d]", MatrizBussola.Matriz[x][j]);
						}

						printf("\n");
					}

					MatrizesBussola.push_back(MatrizBussola);

					printf("\n");
				}
			}

			//faz o mesmo para os arquivos do novo frame
			for (int j = 0; j < countNewColunas; j++)
			{
				char arquivoNew[26];
				_snprintf(arquivoNew, 26, "new histograma %d.txt", j);

				std::ifstream fileNew(arquivoNew);

				if (!fileNew)
				{
					continue;
				}

				if (fileNew.is_open())
				{
					//int MatrizNew[8][8];
					A MatrizNew;

					for (int x = 0; x < 8; x++)
					{
						for (int y = 0; y < 8; y++)
						{
							MatrizNew.Matriz[x][y] = 0;
						}
					}

					while (!fileNew.eof())
					{
						std::string lineNew;
						std::getline(fileNew, lineNew);

						std::vector<std::string> splitted_vectorNew = split(lineNew);

						//amarelo para
						if (splitted_vectorNew[0] == "192" && splitted_vectorNew[1] == "192" && splitted_vectorNew[2] == "64")
						{
							//cinza
							if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[0][1] = std::stoi(splitted_vectorNew[8]);
							}
							//vermelho
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[0][2] = std::stoi(splitted_vectorNew[8]);
							}
							//azul
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[0][3] = std::stoi(splitted_vectorNew[8]);
							}
							//verde
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[0][4] = std::stoi(splitted_vectorNew[8]);
							}
							//rosa
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[0][5] = std::stoi(splitted_vectorNew[8]);
							}
							//branco
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[0][6] = std::stoi(splitted_vectorNew[8]);
							}
							//ciano
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[0][7] = std::stoi(splitted_vectorNew[8]);
							}
						}
						//cinza para
						else if (splitted_vectorNew[0] == "64" && splitted_vectorNew[1] == "64" && splitted_vectorNew[2] == "64")
						{
							//amarelo
							if (splitted_vectorNew[0] == "192" && splitted_vectorNew[1] == "192" && splitted_vectorNew[2] == "64")
							{
								MatrizNew.Matriz[1][0] = std::stoi(splitted_vectorNew[8]);
							}
							//vermelho
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[1][2] = std::stoi(splitted_vectorNew[8]);
							}
							//azul
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[1][3] = std::stoi(splitted_vectorNew[8]);
							}
							//verde
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[1][4] = std::stoi(splitted_vectorNew[8]);
							}
							//rosa
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[1][5] = std::stoi(splitted_vectorNew[8]);
							}
							//branco
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[1][6] = std::stoi(splitted_vectorNew[8]);
							}
							//ciano
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[1][7] = std::stoi(splitted_vectorNew[8]);
							}
						}
						//vermelho para
						else if (splitted_vectorNew[0] == "192" && splitted_vectorNew[1] == "64" && splitted_vectorNew[2] == "64")
						{
							//amarelo
							if (splitted_vectorNew[0] == "192" && splitted_vectorNew[1] == "192" && splitted_vectorNew[2] == "64")
							{
								MatrizNew.Matriz[2][0] = std::stoi(splitted_vectorNew[8]);
							}
							//cinza
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[2][1] = std::stoi(splitted_vectorNew[8]);
							}
							//azul
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[2][3] = std::stoi(splitted_vectorNew[8]);
							}
							//verde
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[2][4] = std::stoi(splitted_vectorNew[8]);
							}
							//rosa
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[2][5] = std::stoi(splitted_vectorNew[8]);
							}
							//branco
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[2][6] = std::stoi(splitted_vectorNew[8]);
							}
							//ciano
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[2][7] = std::stoi(splitted_vectorNew[8]);
							}
						}
						//azul para
						else if (splitted_vectorNew[0] == "64" && splitted_vectorNew[1] == "64" && splitted_vectorNew[2] == "192")
						{
							//amarelo
							if (splitted_vectorNew[0] == "192" && splitted_vectorNew[1] == "192" && splitted_vectorNew[2] == "64")
							{
								MatrizNew.Matriz[3][0] = std::stoi(splitted_vectorNew[8]);
							}
							//cinza
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[3][1] = std::stoi(splitted_vectorNew[8]);
							}
							//vermelho
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[3][2] = std::stoi(splitted_vectorNew[8]);
							}
							//verde
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[3][4] = std::stoi(splitted_vectorNew[8]);
							}
							//rosa
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[3][5] = std::stoi(splitted_vectorNew[8]);
							}
							//branco
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[3][6] = std::stoi(splitted_vectorNew[8]);
							}
							//ciano
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[3][7] = std::stoi(splitted_vectorNew[8]);
							}
						}
						//verde para
						else if (splitted_vectorNew[0] == "64" && splitted_vectorNew[1] == "192" && splitted_vectorNew[2] == "64")
						{
							//amarelo
							if (splitted_vectorNew[0] == "192" && splitted_vectorNew[1] == "192" && splitted_vectorNew[2] == "64")
							{
								MatrizNew.Matriz[4][0] = std::stoi(splitted_vectorNew[8]);
							}
							//cinza
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[4][1] = std::stoi(splitted_vectorNew[8]);
							}
							//vermelho
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[4][2] = std::stoi(splitted_vectorNew[8]);
							}
							//azul
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[4][3] = std::stoi(splitted_vectorNew[8]);
							}
							//rosa
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[4][5] = std::stoi(splitted_vectorNew[8]);
							}
							//branco
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[4][6] = std::stoi(splitted_vectorNew[8]);
							}
							//ciano
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[4][7] = std::stoi(splitted_vectorNew[8]);
							}
						}
						//rosa para
						else if (splitted_vectorNew[0] == "192" && splitted_vectorNew[1] == "64" && splitted_vectorNew[2] == "192")
						{
							//amarelo
							if (splitted_vectorNew[0] == "192" && splitted_vectorNew[1] == "192" && splitted_vectorNew[2] == "64")
							{
								MatrizNew.Matriz[5][0] = std::stoi(splitted_vectorNew[8]);
							}
							//cinza
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[5][1] = std::stoi(splitted_vectorNew[8]);
							}
							//vermelho
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[5][2] = std::stoi(splitted_vectorNew[8]);
							}
							//azul
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[5][3] = std::stoi(splitted_vectorNew[8]);
							}
							//verde
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[5][4] = std::stoi(splitted_vectorNew[8]);
							}
							//branco
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[5][6] = std::stoi(splitted_vectorNew[8]);
							}
							//ciano
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[5][7] = std::stoi(splitted_vectorNew[8]);
							}
						}
						//branco para
						else if (splitted_vectorNew[0] == "192" && splitted_vectorNew[1] == "192" && splitted_vectorNew[2] == "192")
						{
							//amarelo
							if (splitted_vectorNew[0] == "192" && splitted_vectorNew[1] == "192" && splitted_vectorNew[2] == "64")
							{
								MatrizNew.Matriz[6][0] = std::stoi(splitted_vectorNew[8]);
							}
							//cinza
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[6][1] = std::stoi(splitted_vectorNew[8]);
							}
							//vermelho
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[6][2] = std::stoi(splitted_vectorNew[8]);
							}
							//azul
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[6][3] = std::stoi(splitted_vectorNew[8]);
							}
							//verde
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[6][4] = std::stoi(splitted_vectorNew[8]);
							}
							//rosa
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[6][5] = std::stoi(splitted_vectorNew[8]);
							}
							//ciano
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[6][7] = std::stoi(splitted_vectorNew[8]);
							}
						}
						//ciano para
						else if (splitted_vectorNew[0] == "64" && splitted_vectorNew[1] == "192" && splitted_vectorNew[2] == "192")
						{
							//amarelo
							if (splitted_vectorNew[0] == "192" && splitted_vectorNew[1] == "192" && splitted_vectorNew[2] == "64")
							{
								MatrizNew.Matriz[7][0] = std::stoi(splitted_vectorNew[8]);
							}
							//cinza
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[7][1] = std::stoi(splitted_vectorNew[8]);
							}
							//vermelho
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[7][2] = std::stoi(splitted_vectorNew[8]);
							}
							//azul
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[7][3] = std::stoi(splitted_vectorNew[8]);
							}
							//verde
							else if (splitted_vectorNew[4] == "64" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "64")
							{
								MatrizNew.Matriz[7][4] = std::stoi(splitted_vectorNew[8]);
							}
							//rosa
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "64" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[7][5] = std::stoi(splitted_vectorNew[8]);
							}
							//branco
							else if (splitted_vectorNew[4] == "192" && splitted_vectorNew[5] == "192" && splitted_vectorNew[6] == "192")
							{
								MatrizNew.Matriz[7][6] = std::stoi(splitted_vectorNew[8]);
							}
						}
					}

					printf("===== %d =====\n", j);

					for (int x = 0; x < 8; x++)
					{
						for (int y = 0; y < 8; y++)
						{
							printf("[%d]", MatrizNew.Matriz[x][y]);
						}

						printf("\n");
					}

					MatrizesNew.push_back(MatrizNew);

					printf("\n");
				}

				//system("cls");
				printf("\a");
			}
		}
		else if (op == 8)
		{
			system("cls");

			printf("Calculo de similaridade - cosine_similarity\n\n");
			printf("\n\nDistância Euclideana, Bhattacharya, Bayesian, Mahalanobis, Manhathan   ????\n\n");

			int bussolaCol = 0;
			int newCol = 0;

			std::list<CossineOrder> cossine;

			std::ofstream myfile;
			myfile.open("cosine.txt", std::ios_base::app);

			for (std::list<A>::iterator it = MatrizesBussola.begin(); it != MatrizesBussola.end(); ++it)
			{
				double similaridadeAnterior = 0;
				int colunaMaisSimilar = 0;

				CossineOrder coss;

				for (std::list<A>::iterator itN = MatrizesNew.begin(); itN != MatrizesNew.end(); ++itN)
				{
					double similaridade = 0.0;
					double denom_a = 0.0, denom_b = 0.0;

					//coluna para linha ou linha para coluna?
					for (int j = 0; j < 8; j++)
					{
						for (int i = 0; i < 8; i++)
						{
							//http://stackoverflow.com/questions/30404099/right-way-to-compute-cosine-similarity-between-two-arrays
							similaridade += it->Matriz[i][j] * itN->Matriz[i][j];
							denom_a += it->Matriz[i][j] * it->Matriz[i][j];
							denom_b += itN->Matriz[i][j] * itN->Matriz[i][j];
						}
					}

					similaridade = similaridade / (sqrt(denom_a) * sqrt(denom_b));

					if (similaridade > similaridadeAnterior)
					{
						similaridadeAnterior = similaridade;
						colunaMaisSimilar = newCol;
					}

					//printf("cosine_similarity entre bussola %d e new %d = %f \n", bussolaCol, newCol, similaridade);

					myfile << "cosine_similarity entre bussola ";
					myfile << bussolaCol;
					myfile << " e new ";
					myfile << newCol;
					myfile << " = ";
					myfile << similaridade;
					myfile << ")\n";

					newCol++;
				}

				printf("Cosine_similarity entre bussola %d e Frame %d = %f \n", bussolaCol, colunaMaisSimilar, similaridadeAnterior);

				coss.bussola = bussolaCol;
				coss.ColNew = colunaMaisSimilar;
				coss.valor = similaridadeAnterior;

				cossine.push_back(coss);

				bussolaCol++;
				newCol = 0;
			}

			myfile.close();

			//percorrer a lista com os maiores valores para cada coluna

			printf("\a");
		}
		else if (op == 9)
		{
			system("cls");

			int bussolaCol = 0;
			int newCol = 0;

			std::ofstream myfile;
			myfile.open("c manhatan.txt", std::ios_base::app);

			for (std::list<A>::iterator it = MatrizesBussola.begin(); it != MatrizesBussola.end(); ++it)
			{
				double distancia = 0;

				for (std::list<A>::iterator itN = MatrizesNew.begin(); itN != MatrizesNew.end(); ++itN)
				{
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							//abs(a-c) + abs(b-d)
							distancia += abs(it->Matriz[i][j] - itN->Matriz[i][j]) + abs(it->Matriz[i][j] - itN->Matriz[i][j]);
						}
					}

					distancia = sqrt(distancia);

					printf("Distancia entre bussola %d e new %d = %f \n", bussolaCol, newCol, distancia);

					myfile << "Distancia entre bussola ";
					myfile << bussolaCol;
					myfile << " e new  ";
					myfile << newCol;
					myfile << " = ";
					myfile << distancia;
					myfile << ")\n";

					newCol++;
				}


				bussolaCol++;
				newCol = 0;
			}

			myfile.close();

			printf("\a");
		}
		else if (op == 10)
		{
			system("cls");

			int bussolaCol = 0;
			int newCol = 0;

			std::ofstream myfile;
			myfile.open("c jaccard.txt", std::ios_base::app);

			for (std::list<A>::iterator it = MatrizesBussola.begin(); it != MatrizesBussola.end(); ++it)
			{
				double similaridade = 0;

				for (std::list<A>::iterator itN = MatrizesNew.begin(); itN != MatrizesNew.end(); ++itN)
				{
					int common_tokens = 0;
					int total_distinct_tokens = 0; // tokens1.size() + tokens2.size() - common_tokens;
					double similarity = (double)common_tokens / total_distinct_tokens;
					/*

					double Similarity::JaccardSimilarity(string &s1, string &s2)
					{
					vector <string> tokens1;
					vector <string> tokens2;
					Tokenize_with_delimiter(s1, &tokens1, " ?\t\".,;!\n");
					Tokenize_with_delimiter(s2, &tokens2, " ?\t\".,;!\n");
					int common_tokens = num_common_tokens(tokens1,tokens2);
					int total_distinct_tokens = tokens1.size() + tokens2.size() - common_tokens;
					double similarity = (double)common_tokens/total_distinct_tokens;
					return similarity;
					}

					void Similarity::JaccardSimilarityEval()
					{
					for(int i=0;i<(int)data.size();i++)
					{
					double score = JaccardSimilarity(data[i].s1, data[i].s2);
					cout<<"1. "<<data[i].s1<<"\n2. "<<data[i].s2<<"\n"<<score<<"\n"<<data[i].quality<<"\n\n";
					scores.push_back(score);
					if((i+1)%100 == 0)
					cout<<"computed similarity scores for "<<i+1<<" pairs\n";

					}
					}

					*/

					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							//abs(a-c) + abs(b-d)
							similaridade += abs(it->Matriz[i][j] - itN->Matriz[i][j]) + abs(it->Matriz[i][j] - itN->Matriz[i][j]);
						}
					}

					printf("similaridade entre bussola %d e new %d = %f \n", bussolaCol, newCol, similaridade);

					myfile << "similaridade entre bussola ";
					myfile << bussolaCol;
					myfile << " e new  ";
					myfile << newCol;
					myfile << " = ";
					myfile << similaridade;
					myfile << ")\n";

					newCol++;

					similaridade = 0;
				}


				bussolaCol++;
				newCol = 0;
			}

			myfile.close();

			printf("\a");
		}
		else if (op == 11)
		{
			system("cls");

			int bussolaCol = 0;
			int newCol = 0;

			std::ofstream myfile;
			myfile.open("c euclideana.txt", std::ios_base::app);

			for (std::list<A>::iterator it = MatrizesBussola.begin(); it != MatrizesBussola.end(); ++it)
			{
				double distancia = 0;

				for (std::list<A>::iterator itN = MatrizesNew.begin(); itN != MatrizesNew.end(); ++itN)
				{
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							//euclidiana
							//distancia = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));

							distancia += (it->Matriz[i][j] - itN->Matriz[i][j]) * (it->Matriz[i][j] - itN->Matriz[i][j]);
						}
					}

					distancia = sqrt(distancia);

					printf("Distancia entre bussola %d e new %d = %f \n", bussolaCol, newCol, distancia);

					myfile << "Distancia entre bussola ";
					myfile << bussolaCol;
					myfile << " e new  ";
					myfile << newCol;
					myfile << " = ";
					myfile << distancia;
					myfile << ")\n";

					distancia = 0;

					newCol++;
				}


				bussolaCol++;
				newCol = 0;
			}

			myfile.close();

			printf("\a");
		}
		else if (op == 12)
		{
			system("cls");

			int bussolaCol = 0;
			int newCol = 0;

			for (std::list<A>::iterator it = MatrizesBussola.begin(); it != MatrizesBussola.end(); ++it)
			{
				double distancia = 0;

				for (std::list<A>::iterator itN = MatrizesNew.begin(); itN != MatrizesNew.end(); ++itN)
				{
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							//euclidiana
							//distancia = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));

							distancia += (itN->Matriz[i][j] - it->Matriz[i][j]) * (itN->Matriz[i][j] - it->Matriz[i][j]);
						}
					}

					distancia = sqrt(distancia);

					printf("Distancia entre bussola %d e new %d = %f \n", bussolaCol, newCol, distancia);

					newCol++;

					distancia = 0;
				}

				bussolaCol++;
				newCol = 0;
			}


			printf("\a");
		}
		else if (op == 13)
		{
			system("cls");

			std::list<Correlacoes> lista;

			int bussolaCol = 0;
			int newCol = 0;

			for (std::list<A>::iterator it = MatrizesBussola.begin(); it != MatrizesBussola.end(); ++it)
			{
				int correlacao = 0;

				for (std::list<A>::iterator itN = MatrizesNew.begin(); itN != MatrizesNew.end(); ++itN)
				{
					correlacao = 0;

					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							correlacao += (itN->Matriz[i][j] * it->Matriz[i][j]);//dividir pela media cada valor
							//printf("%d * %d = %d --> %d\n", it->Matriz[i][j], itN->Matriz[i][j], itN->Matriz[i][j] * it->Matriz[i][j], correlacao);
						}
					}

					//correlacao = sqrt(correlacao);

					printf("Correlação cruzada entre bussola %d e new %d = %d \n", bussolaCol, newCol, correlacao);

					Correlacoes corr;
					corr.correlacao = correlacao;
					corr.colBuss = bussolaCol;
					corr.colNew = newCol;

					lista.push_back(corr);

					newCol++;
				}

				bussolaCol++;
				newCol = 0;
			}

			for (std::list<Correlacoes>::iterator it = lista.begin(); it != lista.end(); ++it)
			{
				printf("Correlação cruzada entre bussola %d e new %d = %d \n", it->colBuss, it->colNew, it->correlacao);
			}

			int x = 0;

			std::list<CorrelacoesSoma> listaSoma;

			for (std::list<Correlacoes>::iterator it = lista.begin(); it != lista.end(); ++it)
			{
				CorrelacoesSoma soma;

				/*soma.de = x;
				soma.ate = x + 5;*/
				soma.colunaBussola = it->colBuss;
				soma.colunaNew = it->colNew;

				std::list<Correlacoes>::iterator itAux;
				soma.soma = it->correlacao;

				if (x < lista.size() - 5)
				{
					for (int i = 0; i < 4; i++)
					{
						if (i == 0)
						{
							itAux = it;
							++itAux;
						}
						else
						{
							++itAux;
						}

						soma.soma += itAux->correlacao;
					}
				}

				listaSoma.push_back(soma);

				x++;
			}

			listaSoma.sort(&sort_by_soma);

			std::ofstream myfile;

			myfile.open("correlacao.txt", std::ios_base::app);

			for (std::list<CorrelacoesSoma>::iterator it = listaSoma.begin(); it != listaSoma.end(); ++it)
			{
				printf("Soma correlação cruzada = %d (Inicio em = coluna bussola: %d e ColunaNew: %d)\n", it->soma, it->colunaBussola, it->colunaNew);
				//printf("Soma correlação cruzada de %d até  %d = %d (coluna bussola: %d e ColunaNew: %d)\n", it->de, it->ate, it->soma, it->colunaBussola, it->colunaNew);

				myfile << "Soma correlação cruzada = ";
				myfile << it->soma;
				myfile << "(Inicio em = coluna bussola : ";
				myfile << it->colunaBussola;
				myfile << " e ColunaNew: ";
				myfile << it->colunaNew;
				myfile << ")\n";
			}

			myfile.close();

			printf("\a");
		}
		else if (op == 14)
		{
			system("cls");

			std::list<Correlacoes> lista;

			int bussolaCol = 0;
			int newCol = 0;

			for (std::list<A>::iterator it = MatrizesBussola.begin(); it != MatrizesBussola.end(); ++it)
			{
				int correlacao = 0;

				for (std::list<A>::iterator itN = MatrizesNew.begin(); itN != MatrizesNew.end(); ++itN)
				{
					correlacao = 0;

					double media1 = 0;
					double media2 = 0;

					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							media1 += ((double)itN->Matriz[i][j]);
						}
					}

					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							media2 += ((double)it->Matriz[i][j]);
						}
					}

					media1 = media1 / (8 * 8);
					media2 = media2 / (8 * 8);

					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							correlacao += (((double)itN->Matriz[i][j] - media1) * ((double)it->Matriz[i][j] - media2));
							//printf("%d * %d = %d --> %d\n", it->Matriz[i][j], itN->Matriz[i][j], itN->Matriz[i][j] * it->Matriz[i][j], correlacao);
						}
					}

					//correlacao = sqrt(correlacao);

					printf("Correlação cruzada entre bussola %d e new %d = %d \n", bussolaCol, newCol, correlacao);

					Correlacoes corr;
					corr.correlacao = correlacao / MatrizesBussola.size();//certo?
					corr.colBuss = bussolaCol;
					corr.colNew = newCol;

					lista.push_back(corr);

					newCol++;
				}

				bussolaCol++;
				newCol = 0;
			}

			for (std::list<Correlacoes>::iterator it = lista.begin(); it != lista.end(); ++it)
			{
				//printf("Correlação cruzada entre bussola %d e new %d = %d \n", it->colBuss, it->colNew, it->correlacao);
			}

			int x = 0;

			std::list<CorrelacoesSoma> listaSoma;

			for (std::list<Correlacoes>::iterator it = lista.begin(); it != lista.end(); ++it)
			{
				CorrelacoesSoma soma;

				/*soma.de = x;
				soma.ate = x + 5;*/
				soma.colunaBussola = it->colBuss;
				soma.colunaNew = it->colNew;

				std::list<Correlacoes>::iterator itAux;
				soma.soma = it->correlacao;

				if (x < lista.size() - 5)
				{
					for (int i = 0; i < 4; i++)
					{
						if (i == 0)
						{
							itAux = it;
							++itAux;
						}
						else
						{
							++itAux;
						}

						soma.soma += itAux->correlacao;
					}
				}

				listaSoma.push_back(soma);

				x++;
			}

			listaSoma.sort(&sort_by_soma);

			std::ofstream myfile;

			myfile.open("correlacaoCompleta.txt", std::ios_base::app);

			for (std::list<CorrelacoesSoma>::iterator it = listaSoma.begin(); it != listaSoma.end(); ++it)
			{
				//--//printf("Soma correlação cruzada = %d (Inicio em = coluna bussola: %d e ColunaNew: %d)\n", it->soma, it->colunaBussola, it->colunaNew);
				//printf("Soma correlação cruzada de %d até  %d = %d (coluna bussola: %d e ColunaNew: %d)\n", it->de, it->ate, it->soma, it->colunaBussola, it->colunaNew);

				myfile << "Soma correlação cruzada = ";
				myfile << it->soma;
				myfile << "(Inicio em = coluna bussola : ";
				myfile << it->colunaBussola;
				myfile << " e ColunaNew: ";
				myfile << it->colunaNew;
				myfile << ")\n";
			}

			myfile.close();

			printf("\a");
		}
		else if (op == 99)
		{
			cv::Mat image;
			image = cv::imread("360_2.jpg", CV_LOAD_IMAGE_COLOR);
			//image = lerImage1();

			//se iamgme grande demasiadamente. pq??
			//cv::flip(image, image, 1);
			cv::flip(image, image, -1);

			int erosion_size = 2;
			Mat element = getStructuringElement(cv::MORPH_OPEN,
				cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
				cv::Point(erosion_size, erosion_size));

			erode(image, image, element);

			cv::dilate(image, image, (5, 5), Point(-1, -1), 1, 1, 1);
			cv::morphologyEx(image, image, MORPH_OPEN, (15, 15));

			cv::imwrite("360_2-.jpg", image);
			
			cv::Mat hsv;

			cv::cvtColor(image, hsv, CV_BGR2HSV);
			cv::Mat aux = hsv.clone();

			cv::imwrite("360_2--.jpg", aux);

			colorReduce(aux);

			cv::imwrite("360_2---.jpg", aux);
			//cv::imwrite("colorReduced.jpg", aux);

			for (int i = 0; i < aux.rows; i++)
			{
				for (int x = 0; x < 10; x++)
				{
					for (int j = x; j < aux.cols; j = j + 20)
					{
						Vec3b bgrPixel = aux.at<Vec3b>(i, j);

						if (i == 0 && j % 10 == 0)
						{
							cv::rectangle(aux, cvRect(j, i, 10, aux.rows), CvScalar(0, 128, 255), 1, 1, 0);
						}

						try
						{
							if (bgrPixel.val[0] < 200)
								bgrPixel.val[0] = bgrPixel.val[0] + 50; // B
							if (bgrPixel.val[1] < 200)
								bgrPixel.val[1] = bgrPixel.val[1] + 50; // G
							if (bgrPixel.val[2] < 200)
								bgrPixel.val[2] = bgrPixel.val[2] + 50; // R

							aux.at<Vec3b>(i, j) = bgrPixel;
						}
						catch (int e)
						{
							continue;
						}
					}
				}
			}

			cv::imwrite("360_2----.jpg", aux);

			cv::imshow("Imagem Resultante", aux);
			cv::waitKey(0);
		}
		else if (op != 0)
		{
			system("cls");

			printf("Digite uma opcao valida\n\n");

			printf("\a");
		}
	} while (op != 0);

	return 0;
}