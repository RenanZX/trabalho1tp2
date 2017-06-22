#ifndef TEMPO_H
#define TEMPO_H


class tempo{

    private:
        time_t static inicio;
        time_t static fim;


    public:
        tempo();
        virtual ~tempo();
        void inciaContagem() throw (runtime_error);
        void terminaContagem() throw (runtime_error);
        double tempoGasto() throw (runtime_error);

};

#endif // TEMPO_H
