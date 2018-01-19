#pragma once
/////////////////////////////////////////////////////////////////////////////
//
// Singleton - modèle Singleton applicable à n'importe quelle classe.
// nope:
// http://tfc.duke.free.fr/coding/singleton.html
// https://openclassrooms.com/forum/sujet/sfml-singleton-31775
// yes:
// http://www.yolinux.com/TUTORIALS/C++Singleton.html
/////////////////////////////////////////////////////////////////////////////
#ifndef __SINGLETON_HPP_
#define __SINGLETON_HPP_
#include <cassert>

template <class T>
class Singleton
{
public:
  static T* Instance() {
      if(!m_pInstance) m_pInstance = new T;
      assert(m_pInstance != nullptr);
      return m_pInstance;
  }
protected:
  Singleton();
  ~Singleton();
private:
  Singleton(Singleton const&);
  Singleton& operator=(Singleton const&);
  static T* m_pInstance;
};

template <class T> T* Singleton<T>::m_pInstance= nullptr;

#endif