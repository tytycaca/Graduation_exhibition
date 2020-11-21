**About World Maker**

**YouTube Link :** https://youtu.be/nAqHVnQAzRY

타이틀 : World Maker\
\>\> 자신만의 자유로운 세계를 만들자는 뜻에서 'World Maker' 라고 명명함.

<img src="/Screenshots/title.png">

플랫폼 : PC\
\>\> 보다 많은 유저가 플레이할 수 있게 가장 보편화된 플랫폼인 PC를 선택.

장르 : 샌드박스형 게임\
\>\> 창작이 자유롭다는 점과 샌드박스라는 한정된 공간 안에서의 자유도는
무한하다라는 점에서 샌드박스형 게임으로 분류함.

사용 엔진 : DirectX 11\
\>\> Low Level 부터 구현하고 싶고 Graphics Pipeline 에 관심이 많아
선택하게 됨.

타겟 플레이어 : 전 연령\
\>\> 남녀노소 누구나 자신의 창의적인 세상을 만들 수 있도록 타겟
플레이어를 전 연령층으로 설정함.

**Concept -- 컨셉**

-   **외계 행성을 테라포밍 하자!**

<img src="/Screenshots/Terraforming1.png">
<img src="/Screenshots/Terraforming2.jpg">

\>\> 외계 행성 이주 프로젝트의 선발대가 되어 행성을 탐험해보자!

\>\> 자유롭게 건물을 배치하여 창의적인 나만의 행성을 만드는 오픈 월드
게임.

\>\> 나무와 풀, 바위 등등 여러 오브젝트를 파괴하고 자원을 채취하여
건물을 건설해보자!

**Reference Game -- 레퍼런스 게임**

Minecraft

<img src="/Screenshots/minecraft.jpg">

\>\> 기본적인 컨셉은 마인크래프트에서 가져왔으며, 게임의 궁극적인 목표가
명확히 정해져있지 않고 유저의 상상력에 기반한 플레이 방식을 참고하였음.\
마인크래프트에서 블록을 부수고 아이템을 모아서 여러 건물이나 장치를
만드는 것 처럼 World Maker 에서도 자원을 획득하고 건물을 짓는 것이
가능함.

<img src="/Screenshots/starcraftbuild.jpg">

\>\> 다만 마인크래프트와 달리 스타크래프트와 같은 RTS 장르의 게임에서
주로 채용하는 시스템인 '테크 트리 시스템'을 채용하여 단순 아이템만
모였다고 건물을 지을 수 있는 것이 아닌 계획을 세우고 복잡한 플레이를
하게끔 유도함.\
샌드박스형 게임의 특성상 창의력이 부족한 사람들은 재미를 느끼지 못하고
쉽게 게임을 접게 되는데 이를 어느정도 방지하기 위하여 전략적인 요소를
가미한 것임.

Satisfactory

<img src="/Screenshots/satisfactory.jpg">

\>\> 게임의 배경이 되는 컨셉은 Satisfactory 라는 게임에서 가져왔음.\
외계 행성이 배경이 되는 게임으로 행성의 이주민이 되어서 첫 개척자로서
역할을 수행하는 게임으로, 마인크래프트에 공학적인 요소가 가미된 게임.\
World Maker 에서 새로운 개척지를 찾아 미지의 행성으로 떠나고 생존에
적합한 행성을 찾아서 테라포밍 한다는 컨셉을 이 게임에서 가져왔음.

<img src="/Screenshots/box.jpg">
\>\> World Maker 에서 지을 수 있는 건물들
중 하나인 Sci-Fi Crate 인데 이런 종류의 컨셉을 가진 건물들은
Satisfactory 에서 착안함.


**Game Overview -- 게임 개요**

-   자유롭게 건물과 오브젝트를 배치하여 플레이어만의 창의적인 월드를
    만드는 샌드박스형 게임.

-   각 오브젝트에는 필요한 자원들이 있으며, 조건을 만족하면 배치하는
    것이 가능함.

-   자원은 필드 위에 떨어져 있으며, 다가가서 상호작용 하는 것으로 획득할
    수 있음.

-   필드 위에 생성되는 각종 채집 가능한 오브젝트들을 부수는 것으로도
    자원 획득 가능.

-   기본적인 조작법 (자원 채취, 건물 배치) 을 알려주는 튜토리얼까지 구현.

<img src="/Screenshots/jewerl1.png"><img src="/Screenshots/jewerl2.png"><img src="/Screenshots/jewerl3.png"><img src="/Screenshots/jewerl4.png"><img src="/Screenshots/jewerl5.png">

\>\> 획득 가능한 자원들 (사파이어, 에메랄드, 다이아몬드, 자수정, 루비,
목재)

<img src="/Screenshots/jewerl7.png"><img src="/Screenshots/box2.jpg">

\>\> 건설 가능한 건물들 (Sci-Fi crate, 그늘막)

**Controls -- 조작법**

<img src="/Screenshots/movekey.png"><img src="/Screenshots/mouse.png">
\
<img src="/Screenshots/ikey.png"><img src="/Screenshots/ekey.png">

**\
**

**Resources -- 리소스**

**katsbits minecraft terance -- 캐릭터 애니메이션 모델**

<img src="/Screenshots/character.png">

\>\> 마인크래프트 주인공 모델을 가져오고 텍스처는 Blender 로 직접 매핑.

**Colorful World Package -- 정적 오브젝트**

<img src="/Screenshots/worldpack.jpg">

\>\> Unity asset store 에서 판매중인 Low-poly 모델 패키지.\
\>\> 필요한 모델들을 .obj 포맷으로 변환하여 사용.

Implementation -- 구현 내용**

-   Multi scene control (Title, Controls, Main1, Main2, Ending)

Title Scene, Controls Scene, Ending Scene 은 PNG 포맷으로 제작된 이미지.

Bitmap 쉐이더를 구현했고 그것을 통해 Title 화면과 Controls 화면을
랜더함.

각 Scene 들은 기본적으로 1600 x 900 의 해상도를 갖고 있으며 창모드로
실행됨.

PNG 이미지로 제작된 Scene 들은 키 입력 (Space, Enter) 을 통해 다음 Scene
으로 진행하며 Main 1, Main 2, Ending Scene 은 각각의 조건을 만족해야만
다음 단계로 진행할 수 있음.

Main 1 에서 Main 2 로 넘어가는 조건은 Sci-Fi Crate 건물을 3 채 건설하는
것이며 Main 2 에서 Ending 으로 넘어가는 조건은 그늘막 건물을 2 채
건설하는 것임.

어느 Scene 에서든지 F5 버튼을 누르면 타이틀 화면으로 돌아갈 수 있고
게임의 진행 상태는 초기화됨.

어느 Scene 에서든지 ESC 버튼을 누르면 게임이 종료됨.

-   Cube map 을 통한 Skybox 구현. (Background image)

Skybox 쉐이더를 구현하여 배경을 랜더함. (이하는 작동 방식)

플레이어 캐릭터를 중심으로 하는 구를 생성하고 캐릭터가 어디로 움직이든
항상 구의 중심에 자리잡게끔 캐릭터의 움직임에 따라 구를 이동시킴.

그리고 해당 구의 안쪽 면에 Cube map 텍스처를 받아와서 랜더함. (마치 방
안에 벽지를 붙이는 것처럼)

-   OBJ parser, MD5 parser 구현.

정적 오브젝트 (Static objects) 들은 .obj 포맷을 사용하였으며, 동적
오브젝트 (Dynamic objects) 는 .md5 포맷을 사용하였음.

정적 오브젝트는 게임 배경을 조성하는데 쓰이는 오브젝트나 캐릭터와
상호작용할 수 있는 각종 오브젝트들에 사용되었음.

동적 오브젝트는 플레이어블 캐릭터의 구현에 사용됨.

각 포맷은 Direct X 11 에서 읽을 수 있게끔 parser 를 구현하였음.

OBJ 포맷은 v / vn / vt / g / s / f 의 파라매터로 구성되어 있으며 각각의
구성 요소는 vertex 좌표값, vertex 노멀값, texture UV 값, name, smoothing
그룹, face (하나의 면을 구성하는 값들을 총칭) 를 나타냄.

MD5 포맷은 md5mesh 와 md5anim 으로 나뉘어져 있으며, md5mesh 는 모델의
메쉬값(모델의 좌표값 등..) 을 가지고 있고, md5anim 은 모델의 스켈레톤
애니메이션에 쓰이는 여러 정보를 담고 있음. (Weight 값 등..)

각각의 Parser 는 각 포맷의 특정 key 값을 통해 인덱싱하여 파라매터를
찾아내고, Direct X 11 에서 읽을 수 있는 정보로 변환하고 정렬하여 buffer
에 저장해 쉐이더로 넘김.

-   Multi lighting 구현.

'World Maker' 에서 사용하는 조명 타입은 두 가지이며, Directional Light
와 Spot Light 를 사용함.

두 조명을 함께 적용시키기 위하여 Light shader 를 HLSL 로 구현하였음.

Light shader 에 넘기는 버퍼의 파라매터에는 ambientColor, diffuseColor,
lightDirection, specularPower, specularColor, pos, range, dir, cone,
att, pading 이 있으며, ambientColor 부터 specularColor 까지는
Directional Light 구현을 위해 사용되고 pos 부터 paing 까지의 값은 Spot
Light 를 구현하기 위해 사용됨.

-   Visual Effects 구현.

'World Maker' 의 비쥬얼 이펙트는 Fire, Blue portal, Red portal 이
있으며, 이 이펙트들은 하나의 shader 로 구현하였음.

Effect shader 는 Multi Texturing 기법을 사용하였음.

3개의 각기 다른 텍스쳐를 정해진 시간 간격에 따라 빠르게 바꿔가며
랜더하여 불꽃이 일렁이고 포탈이 일렁이는 이펙트를 구현하였음.

빌보드 기법을 같이 적용시켜서 완성하려 하였으나 빌보드가 캐릭터 방향을
항상 바라보게끔 하는 작업에서 오류가 발생하여 포기하고 대신 여러장의
빌보드를 각각 다른 방향으로 겹쳐 어느 방향에서 보아도 어느정도는
이펙트가 보이게끔 구현함.

-   런타임 오브젝트 생성 / 제거 구현.

런타임 환경에서 오브젝트를 생성하고 제거하는 기능을 구현하였음.

이 기능은 본 게임에서 건물을 생성하고 해체하는 작업에 사용되는 기술임.

Render 함수 내에 True / False 값을 가지는 변수를 사용하여 오브젝트의
랜더링을 제어하였음.

예를들어 건물을 지을 수 있는 조건이 참이 되었을 때 마우스 왼쪽 버튼으로
Input 을 넣으면 특정 건물 랜더링을 제어하는 bool 변수가 참이 되어
오브젝트를 랜더하게됨. (건물 생성)

또한 해당 건물에 대고 마우스 오른쪽 버튼을 클릭하면 변수가 거짓이 되어
오브젝트를 랜더하지 않게 됨. (건물 해체)

-   캐릭터 애니메이션 구현.

캐릭터 애니메이션은 Skeleton Animation 으로 구현하였으며, md5anim 파일에
저장되있는 정보로 제어함.

Skeleton Animation 기법은 캐릭터가 움직일때마다 md5anim 에 저장되있는
애니메이션 프레임 대로 메쉬가 움직임.

각 애니메이션 프레임을 랜더할때마다 뼈대를 만들고 그 뼈대에 mesh 를
붙여서 캐릭터를 랜더함.

정해진 시간 간격에 따라 애니메이션 프레임 대로 메쉬를 움직이기만 해도
애니메이션은 구현할 수 있지만, 그렇게 되면 너무 어색하므로 각 애니메이션
프레임 사이의 보간 값을 계산하여 적용시켜 자연스러운 애니메이션을
연출함.

보간 계산에는 Slerp 라는 테크닉을 사용하였으며, DirectX 의 xnamath
라이브러리에 있는 XMQuaternionSlerp() 라는 함수를 사용하였음.

-   WASD 키를 이용한 캐릭터 움직임 구현.

DirectX 의 Direct Input 라이브러리를 사용하여 구현하였음.

키보드의 입력값에 따라 각각 W 키를 눌렀을 때는 전진, S 는 후진, S 는
좌로 이동, D 는 우로 이동하게 만듦.

캐릭터 움직임은 Render 함수에서 캐릭터 모델의 좌표값을 버퍼를 통해
Shader 로 넘길 때 Direct Input 으로 받아온 키보드 키의 종류와 누르고
있던 시간에 따라 바꾸는 식으로 구현하였음.

또한 캐릭터가 바라보는 방향은 마우스로 조절하게끔 구현함. (마우스 입력도
Direct Input 으로 받아옴)

-   3인칭 카메라 워크 구현.

본 게임의 시점은 3인칭으로, 캐릭터 애니메이션을 보다 잘 보여주기 위해
해당 시점을 채택함.

WASD 키보드 값을 받아서 움직이는 캐릭터에 따라 카메라도 동기화시켜
움직이게 구현함.

여러 오류가 많이 발생하여 한정적으로 구현된 기술임. (위 아래 시선
움직임은 캐릭터를 따라가지 않고 공중에 고정되어 있음)

-   Sound System 구현.

DirectX 의 Direct Sound 라이브러리를 사용하여 구현하였음.

Sound 는 Effect Sound 와 BGM (BackGround Music) 으로 구성됨.

Effect Sound 는 화면 전환 효과음, 자원 획득 효과음, 건물 건설 효과음,
건물 해체 효과음 이렇게 총 4 가지를 사용하였으며,\
BGM 은 타이틀&조작법 배경음악, 메인스테이지 배경음악, 엔딩 배경음악으로
3 가지의 음악을 사용하였음.

-   UI System 구현 (Inventory, Interactive UI)

Bitmap Shader 를 통해 UI 를 구현하였음.

UI 는 Z-Buffer 상 가장 앞에 위치하게 설정하여 모든 오브젝트들 중에 가장
위쪽에 그려지도록 구현함.

또한 Alpha-blending 을 사용하여 PNG 이미지의 투명도를 살려서 랜더하였음.
(반투명 UI 구현)

인벤토리의 경우 퀘스트에 필요한 아이템을 보여주는 하단 간략 아이템창은
구현하였으나, 실제로 아이템을 옮기고 버리고 할 수 있는 I 키를 눌러 열 수
있는 인벤토리는 제대로 구현하지 못하였음.

-   오브젝트 충돌 체크 구현 (Collision System)

AABB (Axis-Aligned Bounding Box) 를 이용한 충돌 체크를 구현하였음.

AABB 는 오브젝트를 감싸는 박스를 생성하는데 해당 박스의 노멀 벡터들이
World 상의 x, y, z 좌표와 일치함.

생성된 박스를 x, y, z 축으로 나누어 각각 비교하면서 겹치는 부분이 있나
체크하고 겹치는 부분이 하나라도 있으면 Collision True 를 반환하고 어느
부분도 겹치지 않으면 Collision Flase 를 반환하게 구현함.

본 게임에서는 플레이어의 캐릭터가 움직일때마다 Collsion 을 체크하여
통과할 수 없는 오브젝트에 부딪히면 더 이상 진행하지 못하고 제자리
걸음하도록 설정하였음.

또한 상호작용 가능한 오브젝트에 부딪히게 되면 아이템을 획득하게 되고
건물을 부수거나 부술 수 있는 오브젝트에 상호작용 할 때도 해당 오브젝트의
바운딩 박스에서 충돌을 감지하면 상호작용이 가능하도록 설계하였음. (Unity
의 Collider 와 유사함)

**Result -- 구현 내용에 대한 항목별 결과 화면**

\>\> Parser 구현, 캐릭터 움직임, Sound System, 오브젝트 충돌 체크 등의
결과 이미지로 나타내기 힘든 것들은 제외함.

-   Multi scene control (Title, Controls, Main1, Main2, Ending)

<img src="/Screenshots/multisceneresult1.png"><img src="/Screenshots/multisceneresult2.png"><img src="/Screenshots/multisceneresult3.png"><img src="/Screenshots/multisceneresult4.png">

-   Cube map 을 통한 Skybox 구현. (Background image)

<img src="/Screenshots/skybox1.png"><img src="/Screenshots/skybox2.png">

-   Multi lighting 구현.

\>\> 모닥불 주위로 동심원을 그리면서 밝아진 부분이 Spot Light, 나머지
부분들은 Directional Light

<img src="/Screenshots/multilighting.png">

-   Visual Effects 구현.

\>\> 왼쪽부터 핑크 포탈, 모닥불, 블루 포탈

<img src="/Screenshots/visualeffects.png">

-   런타임 오브젝트 생성 / 제거 구현.
<img src="/Screenshots/runtimeobject.png">

-   캐릭터 애니메이션 구현.

<img src="/Screenshots/charanim1.png"><img src="/Screenshots/charanim2.png">
\
<img src="/Screenshots/charanim3.png"><img src="/Screenshots/charanim4.png">

-   UI System 구현 (Inventory, Interactive UI)

<img src="/Screenshots/ui1.png"><img src="/Screenshots/ui2.png">
\
<img src="/Screenshots/ui3.png">

-   3인칭 카메라 워크 구현.

<img src="/Screenshots/camerawalk.png">
