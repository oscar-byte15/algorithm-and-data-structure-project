#ifndef LISTA_H
#define LISTA_H

#include "node_user.h"

template <class L>
class Lista {
    private:
        Node_user<L>* inicio;
        Node_user<L>* fin;
        long long tamanho;

    public:
        Lista() {
            this->inicio = this->fin = nullptr;
            this->tamanho = 0;
        }
        ~Lista() {
            while (!this->estaVacia()) {
                this->eliminarAlPrincipio();
            }
            delete this->inicio;
            delete this->fin;
        }
        void insertarAlInicio(Node_user<L>* nuevo) {
            if (this->tamanho > 0) {
                nuevo->siguiente = this->inicio;
                this->inicio = nuevo;
            }
            else {
                this->inicio = this->fin = nuevo;
            }
            ++this->tamanho;
        }

        void insertarAlFinal(Node_user<L>* nuevo) {
            if (this->tamanho > 0) {
                this->fin->siguiente = nuevo;
                this->fin = nuevo;
                ++this->tamanho;
            }
            else {
                this->insertarAlInicio(nuevo);
            }
        }

        void insertarEnPosicion(long long posicion, Node_user<L>* nuevo) {
            if (posicion < this->tamanho && posicion >= 0) {
                if (posicion == 0) {
                    this->insertarAlInicio(nuevo);
                }
                else if (posicion == this->tamanho - 1) {
                    this->insertarAlFinal(nuevo);
                }
                else {
                    Node_user<L> * nuevo = crearNode_user(nuevo);
                    Node_user<L> * puntero = this->inicio;
                    long long contador = 0;
                    while (contador != posicion - 1) {
                        puntero = puntero->siguiente;
                        ++contador;
                    }
                    nuevo->siguiente = puntero->siguiente;
                    puntero->siguiente = nuevo;
                    ++this->tamanho;
                }
            }
        }

        void eliminarAlPrincipio() {
            if (this->tamanho > 0) {
                if (this->tamanho == 1) {
                    delete this->inicio;
                    this->inicio = this->fin = nullptr;
                }
                else {
                    Node_user<L> * eliminado = this->inicio;
                    this->inicio = eliminado->siguiente;
                    eliminado->siguiente = nullptr;
                    delete eliminado;
                }
                --this->tamanho;
            }
        }

        void eliminarAlFinal() {
            if (this->tamanho <= 1) {
                this->eliminarAlPrincipio();
            }
            else {
                Node_user<L> * eliminado = this->fin;
                Node_user<L> * puntero = this->inicio;
                while (puntero->siguiente != eliminado) {
                    puntero = puntero->siguiente;
                }
                puntero->siguiente = nullptr;
                this->fin = puntero;
                delete eliminado;
                --this->tamanho;
            }
        }

        void eliminarEnPosicion(long long posicion) {
            if (posicion < this->tamanho && posicion >= 0) {
                if (posicion == 0) {
                    this->eliminarAlPrincipio();
                }
                else if (posicion == this->tamanho - 1) {
                    this->eliminarAlFinal();
                }
                else {
                    Node_user<L> *puntero = this->inicio;
                    long long contador = 0;
                    while (contador != posicion - 1) {
                        puntero = puntero->siguiente;
                        ++contador;
                    }
                    Node_user<L> *eliminado = puntero->siguiente;
                    puntero->siguiente = eliminado->siguiente;
                    eliminado->siguiente = nullptr;
                    delete eliminado;
                    --this->tamanho;
                }
            }
        }

        void eliminarPorValor(L elemento) {
            Node_user<L> * puntero = this->inicio;
            long long contador = 0;
            bool encontro = false;
            while (contador < this->tamanho && !encontro) {
                puntero = puntero->siguiente;
                if (puntero->elemento == elemento)
                {
                    encontro = true;
                }
                ++contador;
            }
            if (contador == this->tamanho) {
                return;
            }
            else if (encontro) {
                this->eliminarEnPosicion(contador);
            }
        }

        Node_user<L>* obtenerElementoAlInicio() {
            return this->inicio;
        }
        Node_user<L>*  obtenerElementoAlFinal() {
            return this->fin;
        }

        Node_user<L>* get_n_node(long long posicion) {
            if (posicion < this->tamanho && posicion >= 0) {
                if (posicion == 0) {
                    return this->obtenerElementoAlInicio();
                }
                else if (posicion == this->tamanho - 1) {
                    return this->obtenerElementoAlFinal();
                }
                else {
                    Node_user<L> *puntero = this->inicio;
                    long long contador = 0;
                    while (contador != posicion) {
                        puntero = puntero->siguiente;
                        ++contador;
                    }
                    return puntero;
                }
            }
        }

        long long obtenerPosicionPorMail(L elemento) {
            Node_user<L> * puntero = this->inicio;
            long long contador = 0;
            bool encontro = false;
            while (contador < this->tamanho && !encontro) {
                puntero = puntero->siguiente;
                if (puntero->mail == elemento)
                {
                    encontro = true;
                }
                ++contador;
            }
            if (contador == this->tamanho) {
                return NULL;
            }
            else if (encontro) {
                return contador;
            }
        }
        long long size(){
            return this->tamanho;
        }
        bool estaVacia(){
            return this->tamanho == 0;
        }

         Node_user<L>* get_elem_by_id(long long posicion) {
             if (posicion < this->tamanho && posicion >= 0) {
                 if (posicion == 0) {
                     return this->obtenerElementoAlInicio();
                 }
                 else if (posicion == this->tamanho - 1) {
                     return this->obtenerElementoAlFinal();
                 }
                 else {
                     Node_user<L> *puntero = this->inicio;
                     while (puntero->id != posicion) {
                         puntero = puntero->siguiente;
                     }
                     return puntero;
                 }
             }
         }

};

#endif // LISTA_H
