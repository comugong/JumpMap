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
