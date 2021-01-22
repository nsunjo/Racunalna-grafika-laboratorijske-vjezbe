using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LostMenu : MonoBehaviour
{
    public bool GameIsPaused = false;

    public GameObject lostMenuUI;
    public GameObject crosshair;

    private void Start()
    {
        Resume();
    }

    private void Update()
    {
        if (TimerCountdown.secondsLeft == 0)
        {
            Pause();
        }
    }

    public void Resume()
    {
        lostMenuUI.SetActive(false);
        Time.timeScale = 1f;
        GameIsPaused = false;
        crosshair.SetActive(true);
        Cursor.lockState = CursorLockMode.Locked;
    }

    private void Pause()
    {
        lostMenuUI.SetActive(true);
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
