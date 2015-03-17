//Steven Pan	span3@ucsc.edu
//Project 4: Due 3/11/14

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/cdefs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "rijndael.h"

#define BASE             16
#define NOCRYPT           0
#define DECRYPT           1
#define ENCRYPT           2
#define HEXKEYLENGTH     16
#define KEYBITS         128
#define STICKYBIT     01000

char *execname = NULL;

typedef enum {FALSE = 0, TRUE = 1} bool;

bool strcmp2 (char *str1, char *str2) {
   if (strcmp (str1, str2) == 0) return TRUE;
   return FALSE;
}

//Original code written by Ethan L. Miller (elm@cs.ucsc.edu)
//Found in encrypt.c of aes.tar.
int cryption (char *filename, char *hexkey, struct stat *filestat) {
   char *funcname = "cryption()";
   int status = EXIT_SUCCESS;
   unsigned long rk[RKLENGTH(KEYBITS)];	/* round key */
   unsigned char key[KEYLENGTH(KEYBITS)];/* cipher key */
   char	buf[100];
   int i, nbytes, nwritten , ctr;
   int totalbytes;
   unsigned int k0, k1;
   int fileId = filestat->st_ino;
   int nrounds;				/* # of Rijndael rounds */
   int	fd;
   char *hk0 = malloc ((HEXKEYLENGTH/2) + 1); // hex key0
   char *hk1 = malloc ((HEXKEYLENGTH/2) + 1); // hex key1
   unsigned char filedata[16]; //[16];
   unsigned char ciphertext[16]; //[16];
   unsigned char ctrvalue[16]; //[16];
   // zero out the buffers
   bzero (hk0, sizeof (hk0));
   bzero (hk1, sizeof (hk1));
   bzero (rk, sizeof (rk)); // zero out rk[]
   bzero (key, sizeof (key)); // zero out key[]
   bzero (filedata, sizeof (filedata)); // zero out filedata[]
   bzero (ciphertext, sizeof (ciphertext)); // zero out ciphertext[]
   bzero (ctrvalue, sizeof (ctrvalue)); // zero out ctrvalue[]
   // change the key from chars to an int and write it to the key buffer
   for (i = 0; i < HEXKEYLENGTH/2; ++i) {
      hk0[i] = hexkey[i];
      hk1[i] = hexkey[i + (HEXKEYLENGTH/2)];
   }
   hk0[HEXKEYLENGTH/2] = '\0';
   hk1[HEXKEYLENGTH/2] = '\0';

   k0 = strtoul (hk1, NULL, BASE);
   k1 = strtoul (hk0, NULL, BASE);
   bcopy (&k0, &(key[0]), sizeof (k0));
   bcopy (&k1, &(key[sizeof(k0)]), sizeof (k1));
   
   /* Print the key, just in case */
   for (i = 0; i < sizeof (key); ++i) {
      sprintf (buf+2*i, "%02x", key[sizeof(key)-i-1]);
   }
   fprintf (stderr, "KEY: %s\n", buf);
   
   /*
    * Initialize the Rijndael algorithm.  The round key is initialized by this
    * call from the values passed in key and KEYBITS.
    */
   nrounds = rijndaelSetupEncrypt(rk, key, KEYBITS);

   /*
    * Open the file.
    */
   fd = open(filename, O_RDWR);
   if (fd < 0)
   {
      fprintf(stderr, "Error opening file %s\n", filename);
      return EXIT_FAILURE;
   }

   /* fileID goes into bytes 8-11 of the ctrvalue */
   bcopy (&fileId, &(ctrvalue[8]), sizeof (fileId));

   /* This loop reads 16 bytes from the file, XORs it with the encrypted
      CTR value, and then writes it back to the file at the same position.
      Note that CTR encryption is nice because the same algorithm does
      encryption and decryption.  In other words, if you run this program
      twice, it will first encrypt and then decrypt the file.
   */
   for (ctr = 0, totalbytes = 0; /* loop forever */; ++ctr)
   {
      /* Read 16 bytes (128 bits, the blocksize) from the file */
      nbytes = read (fd, filedata, sizeof (filedata));
      if (nbytes <= 0) {
         break;
      }
      if (lseek (fd, totalbytes, SEEK_SET) < 0)
      {
         perror ("Unable to seek back over buffer");
         exit (-1);
      }

      /* Set up the CTR value to be encrypted */
      bcopy (&ctr, &(ctrvalue[0]), sizeof (ctr));

      /* Call the encryption routine to encrypt the CTR value */
      rijndaelEncrypt(rk, nrounds, ctrvalue, ciphertext);

      /* XOR the result into the file data */
      for (i = 0; i < nbytes; ++i) {
         filedata[i] ^= ciphertext[i];
      }

      /* Write the result back to the file */
      nwritten = write(fd, filedata, nbytes);
      if (nwritten != nbytes)
      {
         fprintf (stderr,
                  "%s: error writing the file (expected %d, got %d at ctr %d\n)",
                  execname, nbytes, nwritten, ctr);
         break;
      }

      /* Increment the total bytes written */
      totalbytes += nbytes;
   }
   close (fd);
   free (hk0);
   free (hk1);
   return status;
}


int encryptFile (char *filename, char *key, struct stat *filestat) {
   assert (filename != NULL && key != NULL && filestat != NULL);
   int status = EXIT_SUCCESS;
   status = cryption (filename, key, filestat);
   if (status != EXIT_SUCCESS)
      printf("Encryption failed");
   status = chmod (filename, (filestat->st_mode | STICKYBIT));
   if (status < 0)
      printf("chmod() failed");
   return status;
}

int decryptFile (char *filename, char *key, struct stat *filestat) {
   assert (filename != NULL && key != NULL && filestat != NULL);
   int status = EXIT_SUCCESS;
   status = cryption (filename, key, filestat);
   if (status != EXIT_SUCCESS)
      printf("Encryption failed");
   status = chmod (filename, (filestat->st_mode ^ STICKYBIT));
   if (status < 0)
      printf("chmod() failed");   
   return status;
}

//Check that inputted variables are all valid.
int scanArgs (int argc, char **argv, int *cryptflag) {
   if (argc != 4) {
      printf("Will only accept 4 functions");
      return EXIT_FAILURE;
   }
   if (strlen (argv[1]) == 1) {
      if (strcmp2 (argv[1], "e")) {
         *cryptflag = ENCRYPT;
      }
	  else if (strcmp2 (argv[1], "d")) {
         *cryptflag = DECRYPT;
      }
	  else {
         printf("Invalid flag");
         return EXIT_FAILURE;
      }
   }
   else {
      printf("Invalid flag");
      return EXIT_FAILURE;
   }
   int keylen = strlen (argv[2]);
   if (keylen <= HEXKEYLENGTH) {
      char *key = argv[2];
      int i;
      for (i = 0; i < keylen; ++i) {
         if (!(key[i] >= '0' && key[i] <= '9') &&
             !(key[i] >= 'A' && key[i] <= 'F') && !(key[i] >= 'a' && key[i] <= 'f')) {
            printf("Not a valid hexadecimal");
            return EXIT_FAILURE;
         }
      }
   }
   else {
      return EXIT_FAILURE;
   }
   char *file = argv[3];
   struct stat *filestat = malloc (sizeof (struct stat));
   if (stat (file, filestat) < 0) {
      printf("File does not exist");
      return EXIT_FAILURE;
   }
   free (filestat);
   return EXIT_SUCCESS;
}

int main (int argc, char **argv) {
   execname = argv[0];
   int exitstatus = EXIT_SUCCESS; // Exit status value.

   int cryptflag = NOCRYPT; // e is ENCRYPT, d is DECRYPT, other is 0;
   char *hexkey = NULL;
   char *filename = NULL;
   if (scanArgs (argc, argv, &cryptflag) != EXIT_SUCCESS) return EXIT_FAILURE;
   int keylen = strlen (argv[2]); // length of the key
   if (keylen == HEXKEYLENGTH) hexkey = argv[2];
   else {
      hexkey = malloc (HEXKEYLENGTH);
	  int i;
      int j = keylen - 1;
      for (i = HEXKEYLENGTH - 1; i >= 0; --i) {
         if (j >= 0) {
            hexkey[i] = argv[2][j];
            --j;
         }else hexkey[i] = '0';
      }
   }
   filename = argv[3];
   struct stat *filestat = malloc (sizeof (struct stat));
   if (stat (filename, filestat) < 0) {
      printf("Could not stat file");
      return EXIT_FAILURE;
   }
   // determine what to do based on sticky bit and flag
   switch (cryptflag) {
      case (ENCRYPT):
         // only encrypt if the sticky bit has not already been set
         if ((filestat->st_mode & S_ISVTX) ? FALSE : TRUE)
            exitstatus = encryptFile (filename, hexkey, filestat);
         break;
      case (DECRYPT):
         // only decrypt if the sticky bit has already been set
         if (filestat->st_mode & S_ISVTX)
            exitstatus = decryptFile (filename, hexkey, filestat);
         break;
      default:
         exitstatus = EXIT_FAILURE;
         break;
   }
   free (filestat);
   if (keylen != HEXKEYLENGTH) free (hexkey);   
   return exitstatus;
}