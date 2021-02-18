using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class WinMenu : MonoBehaviour
{
    public bool GameIsPaused = false;

    public GameObject winMenuUI;
    public GameObject crosshair;

    private void Start()
    {
        Resume();
    }

    private void Update()
    {
        if (CollectedKeysUI.keysCollected == 5)
        {
            Pause();
        }
    }

    public void Resume()
    {
        winMenuUI.SetActive(false);
        Time.timeScale = 1f;
        GameIsPaused = false;
        crosshair.SetActive(true);
        Cursor.lockState = CursorLockMode.Locked;
    }

    private void Pause()
    {
        winMenuUI.SetActive(true);
        Time.timeScale = 0f;
        GameIsPaused = true;
        crosshair.SetActive(false);
        Cursor.lockState = CursorLockMode.None;
    }

    public void LoadMenu()
    {
        Time.timeScale = 1f;
        SceneManager.LoadScene("MainMenu");
    }

    public void QuitGame()
    {
        Application.Quit();
    }
}
