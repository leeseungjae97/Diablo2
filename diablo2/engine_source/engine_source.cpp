// engine_source.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//
#include "framework.h"

// TODO: 라이브러리 함수의 예제입니다.
void fnenginesource()
{
}
// lib -> Linking, dll -> program start
// dll - 메모리 절약, 메모리 공유 사용공간이 적음, 패치가 lib보다 쉬움, 실행 중간에 패치가능
//	   - 외부의존도가 높아짐, 메모리에 올리는 동안 성능저하
// lib - 한번완성되면 안정적임, 라이브러리가 잘못되면 컴파일시 오류, 속도가 빠름
//	   - 내용 변경 시 프로그램을 새로운 버전 배포해야함.


