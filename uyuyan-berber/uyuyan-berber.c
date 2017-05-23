#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <semaphore.h>

#define MUSTERI_SINIRI 10 /* Müşteriler için iş parçası sınırı */

/* semaforlar */
sem_t berberKoltugu;    /* berber koltuğuna karşılıklı münhasır erişim sağlar */
sem_t beklemeOdasi;     /* bekleyen müşterileri sınırlar */
sem_t musteriBekletici; /* bekleyen müşterileri berberin işi bitene kadar bekletir */
sem_t berberUykusu;     /* müşteri gelene kadar berberin uyumasını sağlar */

/* fonksiyonlar */
void* berber();
void* musteri(void* sayi);
void* rastgeleBekle(int saniye);

short tamamlanmaDurumu = 0;

int main(int argc, char** args)
{
    int musteriSayisi, sandalyeSayisi, musteriNumaralari[MUSTERI_SINIRI];

    if (argc != 3)
    {
        printf("\nKullanım Hatası!\nKullanım Şekli:\t uyuyan-berber <Müşteri Sayısı> <Sandalye Sayısı>\n\n");
        return EXIT_FAILURE;
    }

    musteriSayisi = atoi(args[1]);
    sandalyeSayisi = atoi(args[2]);

    if (musteriSayisi > MUSTERI_SINIRI)
    {
        printf("\nMüşteri sınırı: %d\n\n", MUSTERI_SINIRI);
        return EXIT_FAILURE;
    }

    printf("\n\nGirilen Müşteri Sayısı:\t\t%d", musteriSayisi);
    printf("\nGirilen Sandalye Sayısı:\t%d\n\n", sandalyeSayisi);

    for (int i = 0; i < MUSTERI_SINIRI; i++)
    {
        musteriNumaralari[i] = i;
    }

    /* Semaforların oluşturulması */
    sem_init(&berberKoltugu, 0, 1);
    sem_init(&beklemeOdasi, 0, sandalyeSayisi);
    sem_init(&musteriBekletici, 0, 0);
    sem_init(&berberUykusu, 0, 0);

    pthread_t ipBerber, musteriler[MUSTERI_SINIRI];

    /* Berber iş parçasının oluşturulması */
    pthread_create(&ipBerber, NULL, berber, NULL);

    /* Müşteri iş parçalarının oluşturulması */
    for (int i = 0; i < musteriSayisi; i++)
    {
        pthread_create(&musteriler[i], NULL, musteri, (void*)&musteriNumaralari[i]);
        pthread_join(musteriler[i], NULL);
    }

    tamamlanmaDurumu = 1;
    sem_post(&berberUykusu);
    pthread_join(ipBerber, NULL);

    return EXIT_SUCCESS;
}

void* berber()
{

}

void* musteri(void* sayi)
{

}

void* rastgeleBekle(int saniye)
{

}
