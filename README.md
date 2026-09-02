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
├─ 코인 (점수 획득) <br>
├─ 힐링 포션 (HP 회복, 최대 HP는 100) <br>
├─ 지뢰 (닿으면 일정 시간 후에 일정 범위 내에 폭발 데미지 입힘) <br>
└─ 디버프 아이템 <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ 슬로우 (일정 시간 느려짐) <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ 입력 반전 (W와 S, A와 D의 이동이 일정 시간 반전됨) <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ 블라인드 (일정 시간 시야가 어두워짐) <br>
<br>
게임 규칙 <br>
1. 총 3개의 레벨이 존재함 <br>
2. 한 레벨당 3개의 웨이브가 존재함 <br>
2-1. 웨이브 1 (랜덤 아이템 생성) <br>
2-2. 웨이브 2 (웨이브 1 + 맵 바닥에 스파이크(닿으면 데미지 입힘) 생성) <br>
2-3. 웨이브 3 (웨이브 2 + 맵에 일정 시간마다 지뢰가 추가로 생성됨) <br>
3. 다음 웨이브로 넘어가는 조건 <br>
3-1. 맵에 스폰된 코인을 다 먹을 경우 <br>
3-2. 웨이브마다 지정된 시간을 초과할 경우 <br>
4. 게임 종료 조건 <br>
4-1. HP가 0이 될 경우 즉시 종료 <br>
4-2. 3레벨 3웨이브가 종료될 경우 <br>
<br>
인터페이스 <br>
├─ Start/Restart 버튼 <br>
│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ Start 버튼 - 게임을 처음 시작할 때 표시됨 <br>
│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ Restart 버튼 - 게임을 다시 시작할 때 표시됨 <br>
├─ End 버튼 <br>
└─ 인게임 인터페이스 <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ Score - 코인을 획득해서 얻은 점수의 총점을 표시 <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ Level - 현재 레벨과 웨이브를 표시 <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ Debuff - 적용 중인 상태 이상을 표시 <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├─ Time - 현재 웨이브의 남은 시간을 표시 <br>
