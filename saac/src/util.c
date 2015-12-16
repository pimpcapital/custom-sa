#define _UTIL_C_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <netdb.h>
#include <errno.h>
#include <ctype.h>

#include "main.h"
#include "util.h"

#define min( x,y ) ({typeof(x) __x=(x),__y=(y);(__x < __y) ? __x : __y; })
#define max( x,y ) ({typeof(x) __x=(x),__y=(y);(__x < __y) ? __y : __x; })
#define IS_2BYTEWORD( _a_ ) ( (char)(0x80) <= (_a_) && (_a_) <= (char)(0xFF) )
#define PRIME 211
int hashpjw ( char* s )
{
    char *p;
    unsigned int h= 0 ,g;
    for( p = s ; *p ; p ++ ){
        h = ( h<< 4 ) + (*p);
        if( (g = h & 0xf0000000) != 0){
            h = h ^ (g>>24);
            h = h ^ g;
        }
    }
    return h % PRIME;
}

int getHash ( char* s )
{
    int i;
    int h=0;

    for(i=0;; i++){
        if( s[i] == 0 ){
            break;
        }
        h += s[i];
    }
    return h;
}

void easyGetTokenFromString( char *src,int count,char*output,int len )
{
    int i;
    int counter = 0;

    if( len <= 0 )return;

#define ISSPACETAB( c )   ( (c) == ' ' || (c) == '\t' )

    for(i=0;;i++){
        if( src[i]=='\0'){
            output[0] = '\0';
            return;
        }
        if( i > 0 && ! ISSPACETAB( src[i-1] ) &&
            ! ISSPACETAB(  src[i] ) ){
            continue;
        }

        if( ! ISSPACETAB( src[i]) ){
            counter++;
            if( counter == count){
                int j;
                for(j=0;j<len-1;j++){
                    if( src[i+j] == '\0' ||
                        ISSPACETAB( src[i+j] ) ){
                        break;
                    }
                    output[j]=src[i+j];
                }
                output[j]='\0';
                return;

            }
        }

    }
}

void prepareDirectories(char *base)
{
    int i;
    char dname[1024];

    for(i=0;i<256;i++){
        int ret;
        snprintf( dname , sizeof( dname ) , "%s/0x%x", base , i );
        ret = mkdir( dname , 0755 );
        if( ret <0 && errno != EEXIST ){
            log( "mkdir error:%d %s: %s\n", ret ,strerror(errno), dname );
        }
        if( ret == 0 ) log(".");
    }
}

void remove_r( char *s )
{
    int i;
    for(i=0;;i++){
        if(s[i]=='\r')s[i] =0;
        if( s[i]==0)break;
    }
}

void makeDirFilename( char *out , int outlen ,
                  char *base , int dirchar , char *child )
{
    snprintf( out , outlen ,
              "%s/0x%x/%s" , base ,
              dirchar & 0xff , child );
}

int isFile( char *fn )
{
    FILE*fp=fopen(fn,"r");
    if( fp){
        fclose(fp);
        return 1;
    }
    return 0;
}

int createFile( char *fn , char *line )
{
    FILE *fp = fopen( fn , "w" );
    if( fp== NULL ){
        return -1;
    } else {
        fprintf( fp , "%s" , line );
        fclose(fp);
        return 0;
    }
}

#define int int
#define FALSE 0
#define TRUE  1

typedef struct tagEscapeChar
{
    char     escapechar;
    char     escapedchar;
}EscapeChar;
static EscapeChar   escapeChar[]=
{
    { '\n',   'n' },
    { ',',    'c' },
    { '|',    'z' },
    { '\\',   'y' },
};

char*   makeStringFromEscaped( char* src )
{
    int     i;
    int     srclen = strlen( src );
    int     searchindex=0;

    for( i = 0 ; i < srclen ; i ++ ){
    	// for 2Byte Word
    	if( IS_2BYTEWORD( src[i] ) ){
            src[searchindex++] = src[i++];
            src[searchindex++] = src[i];
    	}else{
        if( src[i] == '\\' ){
            int j;

            /*  戚及  侬卞垫仁  */
            i++;
            for( j = 0; j<sizeof(escapeChar)/sizeof(escapeChar[0]); j++){
                if( escapeChar[j].escapedchar == src[i] ){
                    /*  戚互巨旦弗□皿平乓仿分  */
                    src[searchindex++] = escapeChar[j].escapechar;
                    break;
                }
            }
            /*  巨仿□支仃升公及引引戊疋□仄化云仁  */
            if(escapeChar[j].escapedchar != src[i])
            	src[searchindex++] = src[i];
        }else{
            src[searchindex++] = src[i];
        }
      }
    }
    src[searchindex] = '\0';
    return src;
}

char *   makeEscapeString( char* src , char* dest, int sizeofdest)
{
    int         i;
    int     srclen = strlen( src );
    int     destindex=0;

    for( i = 0 ; i < srclen ; i ++ ){
        int dirty=FALSE;
        int     j;
        char    escapechar='\0';
        if( destindex + 1 >= sizeofdest ) break;
		if( IS_2BYTEWORD( src[i] ) ){
	        if( destindex + 2 >= sizeofdest ) break;
            dest[destindex] = src[i];
            dest[destindex+1] = src[i+1];
   	        destindex += 2;
   	        i ++;
   	        continue;
		}

        for( j = 0; j<sizeof(escapeChar)/sizeof(escapeChar[0]); j++){
            if( src[i] == escapeChar[j].escapechar ){
                dirty=TRUE;
                escapechar= escapeChar[j].escapedchar;
                break;
            }
		}
		if( dirty == TRUE ){
			if( destindex + 2 < sizeofdest ){
				dest[destindex] = '\\';
				dest[destindex+1] = escapechar;
				destindex+=2;
				dirty=TRUE;
				continue;       /*  戚及  侬卞褡戈  */
			}else{
				dest[destindex] = '\0';
				return dest;
			}
		}else{
			dest[destindex] = src[i];
			destindex++;
		}
	}

    dest[destindex] = '\0';
    return dest;
}

char *   makeEscapeString1( char* src , char* dest, int sizeofdest)
{
    int         i;
    int     srclen = strlen( src );
    int     destindex=0;

    for( i = 0 ; i < srclen ; i ++ ){
        int dirty=FALSE;
        int     j;
        char    escapechar='\0';
        if( destindex + 1 >= sizeofdest )
            /*  '\0'坌互箫曰卅中及匹仇仇匹蔽曰   */
            break;

	/*	// 蝈剩及ㄠ田奶玄  井升丹井毛民尼永弁
		if( IS_2BYTEWORD( src[i] ) ){
			// 蝈剩分［公及桦宁反ㄠ田奶玄芴坌卞褡引六月［
			// 凶分仄ㄠ田奶玄仄井卅中桦宁反公丹仄卅中
			// 公及引引ㄡ田奶玄鳖霜
	        if( destindex + 2 >= sizeofdest )break;

            dest[destindex] = src[i];
            dest[destindex+1] = src[i+1];
   	        destindex += 2;
   	        i ++;
   	        continue;
		}
	*/
        for( j = 0; j<sizeof(escapeChar)/sizeof(escapeChar[0]); j++)
            if( src[i] == escapeChar[j].escapechar ){
                dirty=TRUE;
                escapechar= escapeChar[j].escapedchar;
                break;
            }

        if( dirty == TRUE ){
            /*  巨旦弗□皿允月  侬分    */
            if( destindex + 2 < sizeofdest ){
                /*  +2 午中丹及反｝ '\\' 午 'n'及仪分   */
                /*  酸曰  侬反蜗坌分    */
                dest[destindex] = '\\';
                dest[destindex+1] = escapechar;
                destindex+=2;
                dirty=TRUE;
                continue;       /*  戚及  侬卞褡戈  */
            }else{
                /*  酸曰田永白央互尕箫仄化中月  */
                dest[destindex] = '\0';
                return dest;
            }
        }else{
            dest[destindex] = src[i];
            destindex++;
        }

    }
    dest[destindex] = '\0';
    return dest;
}
#undef BOOL
#undef FALSE
#undef TRUE



/* 赞中strcatsafe［田永白央互丐孔木月桦宁反窒手仄卅中［ */
int
strcatsafe( char *dest, int destlen , char *append )
{
    int dl = strlen( dest);
    int al = strlen(append);

    if( (dl + al) >= destlen ){
        return -1;
    } else {
        strcat( dest, append );
    }
	return 0;
}

char *chop( char *s )
{
    int l = strlen(s);
    if( l >= 1 ){
        s[l-1]=0;
    }
    return s;
}

// CoolFish: Family 2001/5/30

/*void easyGetTokenFromBuf(char *src, char delim, int count, char *output, int len)
{
    int  i;
    int  counter = 0;
    int  wordflag = 0;
    
    if( len <= 0 ) return;
    
    #define ISSEPARATE( c )   ((c) == delim)
    
    for( i=0; ; i++){
    	if( src[i] == '\0' ){
    		output[0] = '\0';
    		return;
    	}
    	if(IS_2BYTEWORD(src[i])){
    		if( i>0 && wordflag == 1 ){
    			i++;
    			wordflag = 1;
    			continue;
    		}
    		if( i>0 && !ISSEPARATE(src[i-1]) && !ISSEPARATE(src[i])){
    			i++;
    			wordflag = 1;
    			continue;
    		}						
    		wordflag = 1;
    	}else{
    		if( i>0 && wordflag ){
    			wordflag = 0;
    			continue;
    		}
    		if( i>0 && !ISSEPARATE(src[i-1]) && !ISSEPARATE(src[i])){
    			wordflag = 0; 
    			continue;
    		}
    		wordflag = 0;
    	}
        if( !ISSEPARATE(src[i]) ){
        	counter++;
        	if( counter == count ){
        		int j;
        		for ( j=0; j<len-1; j++){
        			if( IS_2BYTEWORD( src[i+j] ) ){
		        		output[j] = src[i+(j++)];
		        		output[j] = src[i+j];
		        	}else{
		        		if( src[i+j]=='\0' || ISSEPARATE(src[i+j])){
		        			break;
		        		}
		        		output[j] = src[i+j];
		        	}
		        }
		        output[j] = '\0';
		        return;
		}
		if( wordflag )
			i++;
		if ( i==0)
		{
			if( IS_2BYTEWORD(src[i]) ){
				wordflag = 1;
				i++;
			}
			else
			{
				wordflag = 0;
			}
		}
	}
    }
}
*/

char* strncpy2( char* dest, const char* src, size_t n )
{
    if( n > 0 ){
        char*   d = dest;
        const char*   s = src;
        int i;
        for( i=0; i<n ; i++ ){
            if( *(s+i) == 0 ){
                /*  戊疋□仄云歹匀凶日 NULL   侬毛  木月   */
                *(d+i) = '\0';
                return dest;
            }
            if( *(s+i) & 0x80 ){
                *(d+i)  = *(s+i);
                i++;
                if( i>=n ){
                    *(d+i-1)='\0';
                    break;
                }
                *(d+i)  = *(s+i);
            }else
                *(d+i) = *(s+i);
        }
    }
    return dest;
}

void strncpysafe( char* dest , const size_t n ,
                  const char* src ,const int length )
{
    /*
     * src 井日 dest 卞 length 戊疋□允月
     * strcpy, strncpy 匹反 dest 方曰 戊疋□允月汹互
     *   五中凛卞裟少午,丢乒伉陆失弁本旦互粟月.
     * 仇及楮醒匹反｝strlen( src ) 午 length 及凝今中幻丹
     * (  端卞戊疋□允月汹) 午 dest 及扔奶术毛  屯化｝
     * strcpysafe 午  元仪毛允月［
     */

    int Short;
    Short = min( strlen( src ) , length );

    /* NULL  侬 毛哔  仄凶  胜 */
    if( n < Short + 1 ){
        /*
         * 田永白央互箫曰卅中及匹 n - 1(NULL  侬)
         * 匹 strncpy 毛裟少
         */
        strncpy2( dest , src , n-1 );
        dest[n-1]='\0';

    }else if( n <= 0 ){
        return;
    }else{
        /*
         * 田永白央反蜗坌卞丐月及匹 Short 匹strncpy毛裟少
         * 卅云 src 卞反 Short 及赢今  卞 NULL 互卅中及匹｝
         * dest 卞反 馨笛仄化云仁［
         */

        strncpy2( dest , src , Short );
        dest[Short]= '\0';

    }
}

void strcpysafe( char* dest ,size_t n ,const char* src )
{
    /*
     * src 井日 dest 尺戊疋□允月.
     * strcpy, strncpy 匹反 dest 方曰 戊疋□允月汹互
     *   五中凛卞裟少午,丢乒伉陆失弁本旦互粟月.
     * 仇木毛  什啃卞, strncpy 互丐月互 strlen( src ) 互 n 方曰
     *   五中凛卞反, dest 及    互 NULL   侬午反卅日卅中.
     *
     * 仄凶互匀化 dest 及  五今方曰 src 及幻丹互赢中凛卞反
     * n-1 匹 strncpy 毛允月. 凝今中凛反公及引引戊疋□允月
     *
     * n 互  及凛反云井仄仁卅月及匹  及凛反 窒手仄卅中［
     *
     */
    // Nuke +1 (08/25): Danger if src=0
    if (!src) {
        *dest = '\0';
        return;
    }
    if( n <= 0 )        /* 窒手仄卅中   */
        return;

    /*  仇及凛鳔匹｝ n >= 1 动晓互瑁烂  */
    /*  NULL  侬毛哔  仄化  胜允月  */
    else if( n < strlen( src ) + 1 ){
        /*
         * 田永白央互箫曰卅中及匹 n - 1(NULL  侬)
         * 匹 strncpy 毛裟少
         */
        strncpy2( dest , src , n-1 );
        dest[n-1]='\0';
    }else
        strcpy( dest , src );

}

char * ScanOneByte( char *src, char delim )
{
	// Nuke
	if (!src) return NULL;

        //   侬  互卅仁卅月引匹腹绸
        for( ;src[0] != '\0'; src ++ ){
          if( IS_2BYTEWORD( src[0] ) ){
              // 蝈剩分［公及桦宁反ㄠ田奶玄芴坌卞褡引六月［
              // 凶分仄ㄠ田奶玄仄井卅中桦宁反公丹仄卅中
              if( src[1] != 0 ){
                  src ++;
              }
              continue;
          }
          //   剩分匀凶［仇仇匹覆擂及  侬午  胜
          if( src[0] == delim ){
              return src;
          }
        }
        // 伙□皿  仃凶日苇勾井日卅井匀凶［
        return NULL;
}

int easyGetTokenFromBuf( char* src ,char* delim ,int count, char* output , int len )
{//ttom this function all change,copy from the second
    int i;          /* 伙□皿  醒 */
    int length =0;  /* 潸曰请仄凶  侬  及赢今 */
    int addlen=0;   /* 箫今木月赢今 */
    int oneByteMode = 0; /* ㄠ田奶玄乒□玉井＂ */

    if( strlen( delim ) == 1 ){ // 腹绸互ㄠ田奶玄卅日ㄠ田奶玄乒□玉卞允月
        oneByteMode = 1;// 公及端ㄡ田奶玄  侬反民尼永弁仄卅中
    }
    for( i =  0 ; i < count ; i ++ ){
         char* last;
         src += addlen;/* 心勾井匀凶赢今毛箫允 */
      
         if( oneByteMode ){
             // ㄠ田奶玄乒□玉分匀凶日仇切日匹腹绸
             last = ScanOneByte( src, delim[0] );
         }else{
                 last  = strstr( src , delim );  /* 苇尥仃月 */
         }
         if( last == NULL ){
            /*
             * 心勾井日卅井匀凶及匹允屯化戊疋□仄化 return［
            */
            strcpysafe( output , len, src );

            if( i == count - 1 )
                /*切斤丹升心勾井匀凶*/
                return 1;
                                                                                                           
                /*心勾井日卅井匀凶*/
             return 0;
          }
          
          /*
           * 心勾井匀凶赭午  赓及匏  及犒毛菲户月
           * 勾引曰嗉濠日木化中月  侬  及赢今
          */
          length = last - src;
                                           
          /*
           * 戚及伙□皿及啃卞心勾井匀凶赢今午 delim 及赢今毛箫仄化云仁
          */
          addlen= length + strlen( delim );
       }
       strncpysafe( output, len , src,length );

       return 1;
}

