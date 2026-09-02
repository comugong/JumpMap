# JumpMap

언리얼 C++로 점프맵 만들기 <br><br>

플랫폼 (Platform) <br>
├─ 회전 플랫폼 (RotatingPlatform) <br>
│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ 회전 플랫폼 1 - Tick, DeltaTime <br>
│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└─ 회전 플랫폼 2 - Timer (5초에 한 번씩 사라짐, 사라지고 5초 후에 다시 나타남) <br>
│ <br>
├─ 이동 플랫폼 (MovingPlatform) <br>
│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ 이동 플랫폼 1 - Tick, DeltaTime (최대 이동 거리 MaxRange, GetActorLocation().Y) <br>
│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└─ 이동 플랫폼 2 - Tick, DeltaTime, Timer, 벡터 배열 (정사각형 모양으로 이동) <br>
│ <br>
└─ 플랫폼 랜덤 생성기 (PlatformSpawner) <br>
<br>
3D 캐릭터 <br>
└─ 탈 것 (Vehicle) <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└─ 6DOF - IA, IMC, Controller, Pawn, 컴포넌트, Tick, DeltaTime, IMC 매핑, 액션 바인딩, 중력 가속도, 에어 컨트롤 <br>
<br>
아이템 (닿으면 효과 발동 후 사라짐)<br>
├─ 코인 (점수 획득, 맵에 있는 코인 다 먹으면 다음 웨이브로 이동함) <br>
├─ 힐링 포션 (HP 회복, 최대 HP는 100) <br>
├─ 지뢰 (닿으면 일정 시간 후에 일정 범위 내에 폭발 데미지 입힘) <br>
└─ 디버프 아이템 <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ 슬로우 (일정 시간 느려짐) <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ 입력 반전 (W와 S, A와 D의 이동이 일정 시간 반전됨) <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ 블라인드 (일정 시간 시야가 어두워짐) <br>
<br>
