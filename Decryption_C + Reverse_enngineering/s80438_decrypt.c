#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>

/* Verschlüsselungsverfahren: AES-192_ECB [Kein Initalisierungsvektor] | EVP_aes_192_ecb() | 16 Byte block size	
 * Bytes Nr 4 und 12 wurden auf 0 gesetzt --> Brutforcen  
 * "https://wiki.openssl.org/index.php/Main_Page" 
 *
 * Funktionsweise:
 * Datei Einlesen + Key Einlesen
 * Bytes 4 und 12 durch probieren ermitteln
 * File auf jpg checken falls JPG --> Ausgeben 
 * Hash bilden mittels EVP-Methoden und diesen ablegen*/

#define Key_file "s80438-key.bin"
#define Ciphertxt "s80438-cipher.bin"

#define BlockSize 16 

int main()
{
	FILE *fin,*keyin,*fout;
	long filesize,keysize;
	unsigned char *blockbuf;
	unsigned char *tmpbuf;
	unsigned char *keybuf;
	unsigned char *enc_plaintext;
	char outfilename[64];



	/*------------------------Key Einlesen---------------------------------------------*/
	if ((keyin = fopen(Key_file, "rb")) == NULL)
	{
    		printf("Error opening %s.\n", Key_file);
    		exit(EXIT_FAILURE);
	}
	fseek(keyin,0,SEEK_END);					
	keysize = ftell(keyin);
	printf("Size of bin-Key: %ld bytes\n",keysize); //davon 4 und 12 Byte 0 --> Brute Force Probieren
	rewind(keyin);
	
	if (!(keybuf=malloc(keysize))) //24 Byte
	{
		printf("out of Memory(keybuf), STOP!\n");
		exit(EXIT_FAILURE);
	}
	fread(keybuf,keysize,1,keyin);					//Key eingelesen und in Keybuf gespeichert, später Byte 4 und 12 anpassen
	fclose(keyin);
	printf("provided Key:\n");							// kann auskommentiert werden wenn gewünscht!
	for(int i=0;i<keysize;i++)
		{
		printf("%d ",keybuf[i]);
		}
	printf("\n");

	/*---------------------File-Einlesen------------------------------------------------*/


  	if ((fin = fopen(Ciphertxt, "rb")) == NULL) 		
	{															
    		printf("Error opening %s.\n", Ciphertxt);
    		exit(EXIT_FAILURE);
	}
	fseek(fin,0,SEEK_END);					
	filesize = ftell(fin);
	printf("Total Size of Ciphertxt: %ld bytes\n",filesize); 
	printf("Blocks: %ld \n",filesize/16);
	rewind(fin);

	if (!(blockbuf=malloc(BlockSize)))
	{
		printf("out of Memory (blockbuf), STOP!\n");
		exit(EXIT_FAILURE);
	}
	fread(blockbuf,BlockSize,1,fin); // ersten block einlesen
	fclose(fin);
	

	if (!(tmpbuf=malloc(BlockSize))) 
	{
		printf("out of Memory (tmpbuf), STOP!\n");
		exit(EXIT_FAILURE);
	}

	/*-------------Block eingelesen, jetzt Key Bruteforcen (und auf JPG header überprüfen) -------------------*/

	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();	// init von ctx

	for(int pos1=0;pos1<256;pos1++)
	{
		keybuf[4]=pos1;
		for(int pos2=0;pos2<256;pos2++)
		{
			keybuf[12]=pos2;

			int tmplen;				// bekommt Wert in DecryptUpdate zugewiesen

			EVP_DecryptInit_ex(ctx, EVP_aes_192_ecb(), NULL , keybuf, NULL); //ctx,type,optional hier NULL ,key,IV hier NULL
			EVP_DecryptUpdate(ctx,tmpbuf, &tmplen , blockbuf, BlockSize);

			if(tmpbuf[0]==0xFF && tmpbuf[1]== 0xD8 && tmpbuf[2]== 0xFF && tmpbuf[3]== 0xE0) //falls JPG
			{

				printf("jpg-header at: Byte4: %d | Byte12: %d, Trying to encrypt whole file\n",pos1,pos2);

				/*Bild decrypten und speichern*/

				if ((fin = fopen(Ciphertxt, "rb")) == NULL)  //text einlesen
					{															
    					printf("Error opening %s.\n", Ciphertxt);
    					exit(EXIT_FAILURE);
					}		
				if (!(enc_plaintext=malloc(filesize)))
					{
						printf("out of Memory (enc_plaintext), STOP!\n");
						exit(EXIT_FAILURE);
					}
				fread(enc_plaintext,filesize,1,fin);   // file in enc_plaintext
				fclose(fin);

				if (!(tmpbuf=malloc(filesize))) 
					{
						printf("out of Memory (tmpbuf), STOP!\n");
						exit(EXIT_FAILURE);
					}
				EVP_DecryptInit_ex(ctx, EVP_aes_192_ecb(), NULL , keybuf, NULL); // Kontext neu initialisieren sonst datei zu groß
				EVP_DecryptUpdate(ctx,tmpbuf, &tmplen , enc_plaintext, filesize);
				printf("encryption done\n");
				int final_len;
				EVP_DecryptFinal_ex(ctx, tmpbuf + tmplen, &final_len); // Padding entfernen
				tmplen += final_len;
    			printf("removed padding\n");
				
			/*	sprintf(outfilename,"Bild.jpg"); //falls gewollt wieder einkommentieren --> Bild anzeigen
				if ((fout = fopen(outfilename, "wb")) == NULL) 
					{															
    					printf("Error opening %s.\n", "outfilename");
    					exit(EXIT_FAILURE);
					}
				fwrite(tmpbuf,tmplen,1,fout);
				fclose(fout); */
				
				/*------------------Aufgabe2:Hashbilden und ablegen-----------------------------------*/
				EVP_add_digest(EVP_sha1()); //hinzufügen eines Objektes anstatt     "OpenSSL_add_all_digests();""
				
				EVP_MD_CTX * mdctx;				
				const EVP_MD* md=EVP_sha1();					//mode
				unsigned char hash_value[EVP_MAX_MD_SIZE];  
				unsigned int hash_len;
				
				mdctx = EVP_MD_CTX_new();
				EVP_DigestInit_ex(mdctx, md, NULL);

				EVP_DigestUpdate(mdctx, tmpbuf, tmplen); 
				EVP_DigestFinal_ex(mdctx, hash_value, &hash_len);

				EVP_MD_CTX_free(mdctx);
				printf("SHA-1 Hash-Wert:\n");
				for(int i=0;i< hash_len;i++)
				{
					printf("%02x",hash_value[i]);
				}
				printf("\n");			// hash gebildet und ausgegeben

				if ((fout = fopen("s80438-dest-hash.bin", "wb")) == NULL)
                    {
                    printf("Error opening %s.\n", "s80438-dest-hash.bin");
					exit(EXIT_FAILURE);
					}
				fwrite(hash_value,hash_len,1,fout);
				fclose(fout);
				printf("s80438-dest-hash.bin created/overwritten\n");
			} 	// ende der if  jpg  schleife


		}
	}	//ende erste for- pos 1 schleife

	EVP_CIPHER_CTX_free(ctx);
	free(enc_plaintext);
	free(blockbuf);
	free(tmpbuf);
	free(keybuf);

	return 0;
}

