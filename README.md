# OCCT_Samples

OCCT 샘플 프로젝트

<br/>

# Build
- Proxy 프로젝트
    - C/C++ → Additional Include Directories → OCCT 헤더 파일 경로 설정
        - `\inc`
    - Linker → Additional Library Directories → OCCT lib 파일 경로 설정
        - `\win64\vc14\libd`

<br/>

- 샘플 프로젝트
        
    - 각 샘플 프로젝트의 빌드 이벤트에 지정된 폴더 경로 수정
 
        ```
        SET OCCT_DLL=C:\OpenCASCADE\Build\win64\vc14\bind
        SET OCCT_THIRD_PARTY=C:\OpenCASCADE\Build\win64\vc14\3rd
        
        xcopy /Y /I /E %OCCT_DLL% $(TargetDir)
        xcopy /Y /I /E %OCCT_THIRD_PARTY% $(TargetDir)
      ```
        - OCCT_DLL : OCCT DLL 폴더 경로 설정
        - OCCT_THIRD_PARTY : OCCT 설치 시 같이 생성된 외부 라이브러리 경로(freetype.dll 등)
            - OCCT 설치 시 생성되는 폴더는 아니며, 따로 생성하여 외부 라이브러리만 모아 놓음.              
        

  
