#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")
#include "basewin.h"
#include <cmath>

class MainWindow : public BaseWindow<MainWindow> {
private:
	ID2D1Factory* pFactory = 0;
	ID2D1HwndRenderTarget* pRenderTarget = 0;
	ID2D1SolidColorBrush* pBrush = 0;
	double roomDepth = 800;
	double distanceToCamera = 1200;
	int windowXPos = 554;
	int windowYPos = 140;

	bool minimized = false;

	double L = 300;
	double stringCoordinates[3] = { 400, 380, roomDepth / 2 };
	double bobCoordinates[3] = { 400, L + 380, roomDepth / 2 };

	double vx = 5;
	double vy = 0;
	double vz = 2;
	double k = 100;
	double b = 0.1;

	HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW);

public:
	void DrawScene() {
		double rescaleRatio = (roomDepth / distanceToCamera) + 1;
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		pRenderTarget->BeginDraw();

		pBrush->SetColor(D2D1::ColorF(0.9f, 0.9f, 1.0f));
		D2D1_RECT_F canvas = D2D1::RectF(0, 0, rc.right, rc.bottom);
		pRenderTarget->FillRectangle(&canvas, pBrush);

		pBrush->SetColor(D2D1::ColorF(0.8f, 0.8f, 0.9f));
		pRenderTarget->DrawLine(D2D1::Point2F(0, 0), 
			D2D1::Point2F(((-960 + windowXPos) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos) / rescaleRatio) + (540 - windowYPos)), pBrush, 2, NULL);
		pRenderTarget->DrawLine(D2D1::Point2F(0, rc.bottom), 
			D2D1::Point2F(((-960 + windowXPos) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos + rc.bottom) / rescaleRatio) + (540 - windowYPos)), pBrush, 2, NULL);
		pRenderTarget->DrawLine(D2D1::Point2F(rc.right, rc.bottom), 
			D2D1::Point2F(((-960 + windowXPos + rc.right) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos + rc.bottom) / rescaleRatio) + (540 - windowYPos)), pBrush, 2, NULL);
		pRenderTarget->DrawLine(D2D1::Point2F(rc.right, 0), 
			D2D1::Point2F(((-960 + windowXPos + rc.right) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos) / rescaleRatio) + (540 - windowYPos)), pBrush, 2, NULL);
		pRenderTarget->DrawLine(D2D1::Point2F(((-960 + windowXPos) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos + rc.bottom) / rescaleRatio) + (540 - windowYPos)), 
			D2D1::Point2F(((-960 + windowXPos) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos) / rescaleRatio) + (540 - windowYPos)), pBrush, 2, NULL);
		pRenderTarget->DrawLine(D2D1::Point2F(((-960 + windowXPos + rc.right) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos + rc.bottom) / rescaleRatio) + (540 - windowYPos)), 
			D2D1::Point2F(((-960 + windowXPos) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos + rc.bottom) / rescaleRatio) + (540 - windowYPos)), pBrush, 2, NULL);
		pRenderTarget->DrawLine(D2D1::Point2F(((-960 + windowXPos + rc.right) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos) / rescaleRatio) + (540 - windowYPos)), 
			D2D1::Point2F(((-960 + windowXPos + rc.right) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos + rc.bottom) / rescaleRatio) + (540 - windowYPos)), pBrush, 2, NULL);
		pRenderTarget->DrawLine(D2D1::Point2F(((-960 + windowXPos) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos) / rescaleRatio) + (540 - windowYPos)), 
			D2D1::Point2F(((-960 + windowXPos + rc.right) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos) / rescaleRatio) + (540 - windowYPos)), pBrush, 2, NULL);

		pBrush->SetColor(D2D1::ColorF(0.0f, 0.0f, 0.0f));
		double bobRescaleRatio = (bobCoordinates[2] / distanceToCamera) + 1;
		D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(((-960 + windowXPos + bobCoordinates[0]) / bobRescaleRatio) + (960 - windowXPos), ((-540 + windowYPos + bobCoordinates[1]) / bobRescaleRatio) + (540 - windowYPos)), 20000.0 / (bobCoordinates[2] + distanceToCamera), 20000.0 / (bobCoordinates[2] + distanceToCamera));
		pRenderTarget->FillEllipse(ellipse, pBrush);

		rescaleRatio = (stringCoordinates[2] / distanceToCamera) + 1;
		pRenderTarget->DrawLine(D2D1::Point2F(((-960 + windowXPos + stringCoordinates[0]) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos + stringCoordinates[1]) / rescaleRatio) + (540 - windowYPos)),
			D2D1::Point2F(((-960 + windowXPos + bobCoordinates[0]) / bobRescaleRatio) + (960 - windowXPos), ((-540 + windowYPos + bobCoordinates[1]) / bobRescaleRatio) + (540 - windowYPos)),
			pBrush, 1, NULL);

		pBrush->SetColor(D2D1::ColorF(0.6f, 0.6f, 0.7f));
		D2D1_ELLIPSE ellipseShadow = D2D1::Ellipse(D2D1::Point2F(((-960 + windowXPos + bobCoordinates[0]) / bobRescaleRatio) + (960 - windowXPos), ((-540 + windowYPos + 800) / bobRescaleRatio) + (540 - windowYPos)), 24000.0 / (bobCoordinates[2] + distanceToCamera), 5000.0 / (bobCoordinates[2] + distanceToCamera));
		pRenderTarget->FillEllipse(ellipseShadow, pBrush);
		pRenderTarget->DrawLine(D2D1::Point2F(((-960 + windowXPos + stringCoordinates[0]) / rescaleRatio) + (960 - windowXPos), ((-540 + windowYPos + 800) / rescaleRatio) + (540 - windowYPos)),
			D2D1::Point2F(((-960 + windowXPos + bobCoordinates[0]) / bobRescaleRatio) + (960 - windowXPos), ((-540 + windowYPos + 800) / bobRescaleRatio) + (540 - windowYPos)),
			pBrush, 1, NULL);

		pRenderTarget->EndDraw();
	}

	void CalculateBobPosition() {
		double dt = 1.0 / 60000.0;
		for (double i = 0; i < (1.0 / 60.0); i += dt) {
			double stringLength = pow(pow(stringCoordinates[0] - bobCoordinates[0], 2) +
				pow(stringCoordinates[1] - bobCoordinates[1], 2) +
				pow(stringCoordinates[2] - bobCoordinates[2], 2), 0.5);
			double accelerationMagnitude = k * (stringLength - L);
			double ax = (stringCoordinates[0] / 100 - bobCoordinates[0] / 100) * accelerationMagnitude - b * vx;
			double ay = ((stringCoordinates[1] / 100 - bobCoordinates[1] / 100) * accelerationMagnitude) + 9.8 - b * vy;
			double az = (stringCoordinates[2] / 100 - bobCoordinates[2] / 100) * accelerationMagnitude - b * vz;
			vx += ax * dt;
			vy += ay * dt;
			vz += az * dt;
			bobCoordinates[0] += 100 * vx * dt;
			bobCoordinates[1] += 100 * vy * dt;
			bobCoordinates[2] += 100 * vz * dt;
		}
	}

	PCWSTR  ClassName() const { return L"Sample Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {

	case WM_SETCURSOR: {
		if (LOWORD(lParam) == HTCLIENT) {
			SetCursor(hCursor);
			return TRUE;
		}
		return 0;
	}

	case WM_ACTIVATE: {
		BOOL fMinimized = (BOOL)HIWORD(wParam);
		minimized = true;
	}

	case WM_SYSCOMMAND: {
		if (wParam == SC_MINIMIZE) {
			minimized = true;
		}
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}

	case WM_TIMER: {
		
		CalculateBobPosition();
		DrawScene();

		return 0;
	}

	case WM_CREATE: {
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory))) {
			return -1;
		}
		RECT rc;
		GetClientRect(m_hwnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
		pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hwnd, size), &pRenderTarget);
		pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0F, 0, 0), &pBrush);
		pBrush->SetColor(D2D1::ColorF(0.0f, 0.0f, 0.0f));

		SetTimer(m_hwnd, 101, 15, NULL);
		return 0;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}

	case WM_GETMINMAXINFO: {
		MINMAXINFO* info = (MINMAXINFO*)lParam;
		info->ptMaxTrackSize.x = 800;
		info->ptMaxTrackSize.y = 800;
		info->ptMinTrackSize.x = 800;
		info->ptMinTrackSize.y = 800;
		return 0;
	}

	case WM_MOVE: {
		int newXPos = (int)(short)LOWORD(lParam);
		int newYPos = (int)(short)HIWORD(lParam);

		if (minimized == false) {
			vx -= (newXPos - windowXPos) / 75.0;
			vy -= (newYPos - windowYPos) / 75.0;
			windowXPos = newXPos;
			windowYPos = newYPos;
		}
		minimized = false;

		CalculateBobPosition();
		DrawScene();
		return 0;
	}

	default: {
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}

	}
	return TRUE;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
	MainWindow win;

	if (!win.Create(hInstance, L"3D PENDULUM", WS_TILEDWINDOW)) {
		return 0;
	}
	ShowWindow(win.Window(), nCmdShow);

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}