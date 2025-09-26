#include <iostream>
#include <openssl/evp.h>
#include <openssl/aes.h>

int main()
{
  unsigned char texto_original[] = "Hola Mundo";
  unsigned char texto_encriptado[256];

  unsigned char clave[16] = "clave0123456789";
  unsigned char iv[16] = "vectorinicial16";
  
  std::cout << "Encriptando: " << texto_original << std::endl;

  EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
  EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, clave, iv);

  int len;
  int texto_encriptado_len;

  EVP_EncryptUpdate(ctx, texto_encriptado, &len, texto_original, sizeof(texto_original)-1);
  texto_encriptado_len = len;

  EVP_EncryptFinal_ex(ctx, texto_encriptado + len, &len);
  texto_encriptado_len += len;

  EVP_CIPHER_CTX_free(ctx);

  std::cout << "Texto encriptado (hex): ";
  for(int i = 0; i < texto_encriptado_len; i++) {
      printf("%02x", texto_encriptado[i]);
  }
  std::cout << std::endl;

  return 0;
}
