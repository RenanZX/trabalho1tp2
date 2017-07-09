#include "ControleTeste_spec.h"
#include "ControledeTeste.h"
#include "Quiz.h"
#include "GerQuiz.h"
#include "igloo.h"

Describe(A_GerQuiz){
    it(Deve_criar_um_quiz){
        GerQuiz gerente;
        gerente.CriaQuiz("Quiz");
    }

    it(Deve_possuir_um_Quiz){
        GerQuiz gerente;
        gerente.SetQuiz("Quiz");
    }

    it(Fazer_Operacoes_Com_Quiz)
    {
        GerQuiz gerente;
        gerente.SetQuiz("Quiz");
        gerente.SetIndexTopicDisc("0-0");
        gerente.SetPerguntaQuiz("0-0.1|PERGUNTA|4|OPT1|OPT2|OPT3|OPT4|2");
        gerente.EditarPergunta("1","pergunta|4|opt1|opt2|opt3|opt4|2");
        gerente.DeletarPerguntaQuiz("1");
    }

    it(Apagar_o_Quiz){
        GerQuiz gerente;
        gerente.SetQuiz("Quiz");
        gerente.DeletarQuizSetado();
    }

};

Describe(A_Quiz)
{
    it(Iniciar_Um_Quiz){
        Quiz q;
    }
};
