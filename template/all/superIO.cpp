namespace superIO {
	//only for reading ints/lls
	//really only useful when input is greater than 10^6
	//but it is super fast
	int BUF=100000;
	int buf_readed = 0;
	int buf_index = 0;
	char buffer[100000];
	/*****************************************/
	char my_getchar(){
	    char x;
	    if(buf_index==buf_readed){
	        buf_index=0;
	        buf_readed=fread(buffer,1,BUF,stdin);
	    }   
	    x=buffer[buf_index];
	    buf_index++;
	    return x;
	}
	/*************************************/

	//can return int or long long
	ll getInt(){
	    ll r=0LL;
	    char c;
	    int sign=1;
	    while(1){
	        c=my_getchar();
	        if(c=='-')
	            sign=-1;
	 
	        if((c>='0' && c<='9')){
	            r=(c-'0');
	            break;
	        }
	    }
	    while(1){
	        c=my_getchar();
	            if(!(c>='0' && c<='9'))
	                break;
	        r=r*10+(c-'0');
	    }
	    return sign*r;
	}
}
using namespace superIO;