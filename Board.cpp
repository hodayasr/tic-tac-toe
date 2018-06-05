#include "Board.h"


using namespace std;

		Board::Board(){
			len = 0;
		}
		
		
		Board::Board(int len){
			this->len = len;
			
			for (int i = 0; i < len; ++i) {
				vector<BoardMem> tmp;
				for (int j = 0; j < len; ++j) {
					BoardMem c{i, j, '.'};
					tmp.push_back(c);
				}
				board.push_back(tmp);
			}
			
		}
		Board::Board(const Board &b2) {
			this->len = b2.len;
			
			for (int i = 0; i < len; ++i) {
				vector<BoardMem> tmp;
				for (int j = 0; j < len; ++j) {
					BoardMem c(i, j, b2.board[i][j].val);
					tmp.push_back(c);
				}
				board.push_back(tmp);
			}
		}
		
		
		BoardMem & Board::operator[](BoardMem const &crdn) {
			
			int x1 = crdn.row;
			int x2 = crdn.col;
			
			if(x1>=len || x2>=len || x1<0 || x2<0){
				IllegalCoordinateException ie(x1,x2);
				throw ie;
			}
			return this->board[x1][x2];
		}
		
		
		
		
		
		
				
		ostream& operator<< (ostream& os, const Board& b){
			for (int i = 0; i < b.len; ++i) {
				for (int j = 0; j < b.len; ++j) {
					os << b.board[i][j];
				}
				os<<endl;
			}
		return os ;
		}
		
		
		
		Board& Board::operator= (char n){
			
			if(n!='.' && n!='O' && n!='X'){
				IllegalCharException ie(n);
				throw ie;
			}
			
			for (int i = 0; i < len; ++i) {
				for (int j = 0; j < len; ++j) {
					board[i][j] = n;
				}
			}
		return *this;
		}
		
		
		
		Board& Board::operator= (Board b2){
			this->len = b2.len;
			vector<vector<BoardMem> > newBoard;
			for (int i = 0; i < len; ++i) {
				vector<BoardMem> tmp;
				for (int j = 0; j < len; ++j) {
					BoardMem c(i, j, b2.board[i][j].val);
					tmp.push_back(c);
				}
				newBoard.push_back(tmp);
			}
			
			board = newBoard;
			return *this;
		}
		
		
		
		istream &operator>>( istream  &input, Board &D ) { 
			string s ;
			string tmp;
			
			int count = 0;
			while(!input.eof()) {
				
				count++;
				s+=tmp;
				input >>tmp;
			}
			
			count--;
			Board bb(count);
			bb.init(s);
			
			D = bb;
			
			return input;            
		}
		
		
		void Board::init(string s){
			int l = 0;
			for(int i=0; i<this->len; i++){
				for(int j=0; j<this->len; j++){
					if(s[l]=='\n') l++;
					if(l<s.size()){
					this->board[i][j] = s[l];
					l++;
					}
				}
			}
		}
		
		
		bool Board::exist(const std::string& name){
				
				ifstream file(name);
				if(!file)            // If the file was not found, then file is 0, i.e. !file=1 or true.
					return false;    // The file was not found.
				else                 // If the file was found, then file is non-0.
					return true;     // The file was found.
					
			}

		string Board::fileName (const std::string& name){
			string s = name;
			bool b = exist(s+".ppm");
			if (b == false){
				return s;
			}
			else return fileName(s + "1");
		}
		
		
		
		
		
		string Board::draw(int dim){
			string nf = fileName("board");//func("board");
			nf+=".ppm";
			paint(nf, dim);
			return nf;
		}
		
		
	

	//RGB *ima;
	void Board::putpixel(int x, int y, int dim, RGB *ima){
		(ima)[dim * (x)+(y)].red = 255;
		(ima)[dim * (x)+(y)].green = 0;
		(ima)[dim * (x)+(y)].blue = 0;
	}

	void Board::drawcircle(int x0, int y0, int radius, int dim, RGB *ima){
		int x = radius-1;
		int y = 0;
		int dx = 1;
		int dy = 1;
		int err = dx - (radius << 1);

		while (x >= y)
		{
			putpixel(x0 + x, y0 + y, dim, ima);
			putpixel(x0 + y, y0 + x, dim, ima);
			putpixel(x0 - y, y0 + x, dim, ima);
			putpixel(x0 - x, y0 + y, dim, ima);
			putpixel(x0 - x, y0 - y, dim, ima);
			putpixel(x0 - y, y0 - x, dim, ima);
			putpixel(x0 + y, y0 - x, dim, ima);
			putpixel(x0 + x, y0 - y, dim, ima);
			
			if (err <= 0)
			{
				y++;
				err += dy;
				dy += 2;
			}
			
			if (err > 0)
			{
				x--;
				dx += 2;
				err += dx - (radius << 1);
			}
		}
	}

	void Board::drawx(int x0, int y0, int radius, int dim, RGB *ima){
		radius *=2;
		x0 = x0 - (radius/2);
		y0 = y0 - (radius/2);
		for(int i=0; i<=radius; i++){
			putpixel(x0+i, y0+i, dim, ima);
			putpixel(radius+x0-i, y0+i, dim, ima);
		}	
	}

	//void paintCell(int row, int col, )

	void Board::paint(string filename, int dim) {
		
		int boardSize = this->len;
		int N = dim;
		
	  const int dimx = N, dimy = N;
	  ofstream imageFile(filename, ios::out | ios::binary);
	  imageFile << "P6" << endl << dimx <<" " << dimy << endl << 255 << endl;
	 
	 RGB image[dimx*dimy];
	  for (int j = 0; j < dimy; ++j)  {  // row
		for (int i = 0; i < dimx; ++i) { // column
		  image[dimx*j+i].red = (255); //image[dimx*row + col]
		  image[dimx*j+i].green = (255);
		  image[dimx*j+i].blue = (255);
		}
	  }
		int line = boardSize-1;
		int cell (dimx / boardSize);
		int mid = (dimx / boardSize )/ 2;
		
		for(int l =1; l<= line; l++){
			int dot = ((dimx/boardSize)*l);
			for (int j = 0; j < dimy; ++j)  {
				
				image[dimx * (dot)+(j)].red = 0;
				image[dimx * (dot)+(j) ].green = 0;
				image[dimx * (dot)+(j)].blue = 0;
				image[dimx *(j)+(dot)].red = 0;
				image[dimx *(j)+(dot)].green = 0;
				image[dimx *(j)+(dot)].blue = 0;
				
		}
	 }
	 RGB *ima = image;
	 for(int i=0; i<len; i++){
		  for(int j=0; j<len; j++){
			  if(board[i][j] == 'O'){
				  drawcircle(cell*i + mid, cell*j + mid, mid - (mid/2), dimx, ima);
			  }
			  if(board[i][j] == 'X'){
				  drawx(cell*i + mid, cell*j + mid, mid - (mid/2), dimx, ima);
			  }
		}
	 }
	 
	  imageFile.write(reinterpret_cast<char*>(&image), 3*dimx*dimy);
	  imageFile.close();
	
	}
