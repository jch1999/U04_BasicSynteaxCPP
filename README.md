### 1. 스크린샷
![주석 2024-10-30 190504](https://github.com/user-attachments/assets/9d1eb163-3c97-441e-b8bf-14c007b7278c)

### 2. 구현해본 기능
- 컴포넌트 생성, 객체 생성
- 델리게이트 실습(Delegate, Event, Multicast, DynamicDelegate)
- 블루프린트 오버라이드(BlueprintImplementableEvent, BlueprintNativeEvent)
  - BlueprintImplementableEvent : 몸체를 BP에서만 구현하는 것
  - BlueprintNativeEvent : CPP에서 기본적인 몸체를 구현할 수 있고 BP에서 재정의 가능하다.

### 3. AnimOffset 사용해보기
  - 원본 애니메이션을 복사한 뒤, 복사한 애니메이션에서 에셋 디테일의 Additive Settings에서 Additive Anim 타입을 MeshSpace로 변경
  - Base Pose Type을 Selected animation frame으로 설정하고 하단에 배이스 애니메이션으로 원본을 넣어준다.
  - 이제 복사된 애니메이션은 AnimOffset에서 사용가능한 애니메이션 에셋이 된다.
  - 이런 애니메이션들에 수정을 가해서 만든 각 애니메이션을 사용해서 본에 보간을 주는 것이 AnimOffset

```C++
void ACAR4::Unequip()
{
    if (!bEquipped) return;
    if (bPlayingMontage) return;

    if (bAutoFiring)
    {
  	  OffFire();
    }

    bPlayingMontage = true;
    OwnerCharacter->PlayAnimMontage(UnequipMontage, MontagesPlayRate);
}
```
