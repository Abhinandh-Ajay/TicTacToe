#include<stdio.h>
#include<conio.h>
#include<iostream.h>
#include<string.h>
#include<process.h>
#include<fstream.h>
#include<dos.h>
#include<ctype.h>
#include<iomanip.h>
struct player
{
	char name[20];
	int wins;
	player()
	{
		wins=0;
	}
};
void display(char A[3][3])
{
	clrscr();
	gotoxy(35,8);
	cout<<" -- -- -- ";
	gotoxy(35,9);
	cout<<"|"<<A[0][0]<<" |"<<A[0][1]<<" |"<<A[0][2]<<" |";
	gotoxy(35,10);
	cout<<" -- -- -- ";
	gotoxy(35,11);
	cout<<"|"<<A[1][0]<<" |"<<A[1][1]<<" |"<<A[1][2]<<" |";
	gotoxy(35,12);
	cout<<" -- -- -- ";
	gotoxy(35,13);
	cout<<"|"<<A[2][0]<<" |"<<A[2][1]<<" |"<<A[2][2]<<" |";
	gotoxy(35,14);
	cout<<" -- -- -- ";
	gotoxy(33,15);
}
void p1(char box[3][3],int &count)
{
	int r,c,x=0;
    display(box);
    cout<<"Player 1's turn";
	while(x==0)
	{
		gotoxy(28,wherey());
		cout<<"Enter the row and column\n";
		r=0,c=0;
		gotoxy(39,wherey());
		cin>>r;
		gotoxy(39,wherey());
		cin>>c;
		r=r-1;
		c=c-1;
		if(r>2||r<0||c>2||c<0||isalpha(r)==!0||isalpha(c)==!0)
		{
			gotoxy(32,wherey());
			cout<<"Incorrect location\n";
		}
		else if(box[r][c]=='X'||box[r][c]=='O')
		{
			gotoxy(31,wherey());
			cout<<"Space already filled\n";
		}
		else
		{
			box[r][c]='X';
			x=1;
			count++;
			clrscr();
			display(box);
		}
	}
}
void p2(char box[3][3],int &count)
{
	int r,c,x=0;
	display(box);
	cout<<"Player 2's turn\n";
	while(x==0)
	{
		gotoxy(28,wherey());
		cout<<"Enter the row and column\n";
		r=0,c=0;
		gotoxy(39,wherey());
		cin>>r;
		gotoxy(39,wherey());
		cin>>c;
		r=r-1;
		c=c-1;
		if(r>2||r<0||c>2||c<0||isalpha(r)==!0||isalpha(c)==!0)
		{
			gotoxy(32,wherey());
			cout<<"Incorrect location\n";
		}
		else if(box[r][c]=='X'||box[r][c]=='O')
		{
			gotoxy(31,wherey());
			cout<<"Space already filled\n";
		}
		else
		{
			box[r][c]='O';
			x=1;
			count++;
			clrscr();
			display(box);
		}
	}
}
void check(char A[3][3],int &checker)
{
	int i;
	for(i=0;i<3;i++)
	{
		if((A[i][0]=='X'&&A[i][1]=='X'&&A[i][2]=='X')||(A[0][i]=='X'&&A[1][i]=='X'&&A[2][i]=='X'))
		{
			checker=1;
		}
	}
	if((A[0][0]=='X'&&A[1][1]=='X'&&A[2][2]=='X')||(A[2][0]=='X'&&A[1][1]=='X'&&A[0][2]=='X'))
	{
		checker=1;
	}
	for(i=0;i<3;i++)
	{
		if((A[i][0]=='O'&&A[i][1]=='O'&&A[i][2]=='O')||(A[0][i]=='O'&&A[1][i]=='O'&&A[2][i]=='O'))
		{
			checker=1;
		}
	}
	if((A[0][0]=='O'&&A[1][1]=='O'&&A[2][2]=='O')||(A[2][0]=='O'&&A[1][1]=='O'&&A[0][2]=='O'))
	{
		checker=1;
	}
}
void score(player win)
{
	player x;
	int pos1,a=0;
	ifstream fin("Score.dat",ios::binary|ios::in);
	pos1=fin.tellg();
	if(pos1>=0)
	{
		while(fin.read((char*)&x,sizeof(x)))
		{
			pos1=0;
			if(strcmpi(win.name,x.name)==0)
			{
				pos1=fin.tellg();
				a=1;
				break;
			}

		}
		fin.close();
		if(a==1)
		{
			ofstream fior("Score.dat",ios::binary|ios::ate);
			fior.seekp(pos1-sizeof(x),ios::beg);
			x.wins=x.wins+1;
			fior.write((char*)&x,sizeof(x));
			fior.close();
		}
		else if(a==0)
		{
			ofstream finr("Score.dat",ios::binary|ios::app);
			win.wins=win.wins+1;
			finr.write((char*)&win,sizeof(win));
			finr.close();
		}
	}
	else
	{
		ofstream fout("Score.dat",ios::binary|ios::app);
		win.wins=win.wins+1;
		fout.write((char*)&win,sizeof(win));
		fout.close();

	}
}
void scoreboard()
{
	player y;
	ifstream fin("Score.dat",ios::binary|ios::in);
	clrscr();
	cout<<"              *****************************************************      \n";
	cout<<"             *    ====    =====   =====   =====    =====   ====    *     \n";
	cout<<"             *   |    |  |       |     |  |    |  |       |    |   *     \n";
	cout<<"             *   |____   |       |     |  |    |  |____   |____    *     \n";
	cout<<"             *        |  |       |     |  |----   |            |   *     \n";
	cout<<"             *   |    |  |       |     |  |   \\   |       |    |   *    \n";
	cout<<"             *    ====    =====   =====   |    \\   =====   ====    *    \n";
	cout<<"             *                                                     *     \n";
	cout<<"              *****************************************************      \n";
	cout<<"                                                                         \n";
	cout<<"            ---------------------------------------------------------    \n";
	cout<<"           |        PLAYER NAME         |       NUMBER OF WINS       |   \n";
	cout<<"           |=========================================================|   \n";
	while(fin.read((char*)&y,sizeof(y)))
	{
		cout.setf(ios::left);
		cout<<"           |"<<setw(28)<<y.name<<"|"<<setw(28)<<y.wins<<"|   \n";
	}
	cout<<"            ---------------------------------------------------------     \n";
	delay(5000);
	fin.close();
}
void main()
{
	clrscr();
	player player1,player2;
	char A[50],box[3][3];
	int i,j,x,op,count=0,checker=0;
	{
		clrscr();
		cout<<"               ================================================= \n";
		cout<<"              |.................................................|\n";
		cout<<"              |            ---------   ----    ---              |\n";
		cout<<"              |            |       |    ||    |                 |\n";
		cout<<"              |            ---   ---   ----    ---              |\n";
		cout<<"              |               | |       --     ---              |\n";
		cout<<"              |               | |      |__|   |                 |\n";
		cout<<"              |               | |      |  |    ---              |\n";
		cout<<"              |               | |       --     ---              |\n";
		cout<<"              |               | |      |  |   |__               |\n";
		cout<<"              |               | |      |  |   |                 |\n";
		cout<<"              |               ---       --     ---              |\n";
		cout<<"              |.................................................|\n";
		cout<<"               ================================================= \n";
		cout<<endl<<endl;
		gotoxy(14,wherey());
		cout<<"|";
		gotoxy(66,wherey());
		cout<<"|";
		for(i=15;i<=66;i++)
		{
			gotoxy(i,17);
			delay(75);
			cout<<"-";
			gotoxy(39,18);
			cout<<(i-15)*2<<"%";
		}
	}
	do
	{
		clrscr();
		for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		box[i][j]=' ';
		cout<<"               ================================================= \n";
		cout<<"              |.................................................|\n";
		cout<<"              |            ---------   ----    ---              |\n";
		cout<<"              |            |       |    ||    |                 |\n";
		cout<<"              |            ---   ---   ----    ---              |\n";
		cout<<"              |               | |       --     ---              |\n";
		cout<<"              |               | |      |__|   |                 |\n";
		cout<<"              |               | |      |  |    ---              |\n";
		cout<<"              |               | |       --     ---              |\n";
		cout<<"              |               | |      |  |   |__               |\n";
		cout<<"              |               | |      |  |   |                 |\n";
		cout<<"              |               ---       --     ---              |\n";
		cout<<"              |.................................................|\n";
		cout<<"               ================================================= \n";
		cout<<endl<<endl;
		gotoxy(32,wherey());
		cout<<"Enter the option:\n                                 1)Start Game!\n                                 2)Scoreboard\n                                 3)Exit Game\n";
		cout<<"\n                                 ";
		cin>>op;
		switch(op)
		{
			case 1:
			clrscr();
			count=0;
			gotoxy(30,10);
			cout<<"Player 1 enter your name:";
			gotoxy(30,11);
			cin>>player1.name;
			gotoxy(30,12);
			cout<<"Player 2 enter your name:\n";
			gotoxy(30,13);
			cin>>player2.name;
			while(count<9)
			{
				checker=0;
				p1(box,count);
				check(box,checker);
				if(checker==1)
				{
					cout<<"Player 1 wins!\n";
					score(player1);
					delay(2000);
					break;
				}
				if(count==9)
				break;
				p2(box,count);
				check(box,checker);
				if(checker==1)
				{
					cout<<"Player 2 wins!\n";
					score(player2);
					delay(2000);
					break;
				}
			}
			if(count==9&&checker==0)
			{
				display(box);
				gotoxy(34,wherey());
				cout<<"It's a draw!\n";
				delay(2000);
				break;
			}
			break;
			case 2:
			scoreboard();
			display(box);
			break;
			case 4:
			remove("Score.dat");
			break;
		}
	}while(op!=3);
	clrscr();
	getch();
}




