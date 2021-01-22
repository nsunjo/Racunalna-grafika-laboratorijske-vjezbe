using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PickUpObject : MonoBehaviour
{
	GameObject mainCamera;
	public Image crosshair = null;
	bool carrying;
	GameObject carriedObject;
	public float distance;
	public float smooth;

	// Use this for initialization
	void Start()
	{
		mainCamera = GameObject.FindWithTag("MainCamera");
	}

	// Update is called once per frame
	void Update()
	{
		if (carrying)
		{
			carry(carriedObject);
			checkDrop();
			rotate();
			collectKey();
			zoom();
		}
		else
		{
			pickup();
		}
	}

	void carry(GameObject o)
	{
		o.transform.position = Vector3.Lerp(o.transform.position, mainCamera.transform.position + mainCamera.transform.forward * distance, Time.deltaTime * smooth);

	}

	void pickup()
	{
		if (Input.GetKeyDown(KeyCode.E))
		{
			int x = Screen.width / 2;
			int y = Screen.height / 2;

			Ray ray = mainCamera.GetComponent<Camera>().ScreenPointToRay(new Vector3(x, y));
			RaycastHit hit;
			if (Physics.Raycast(ray, out hit, 5))
			{
				Pickupable p = hit.collider.GetComponent<Pickupable>();
				if (p != null)
				{
					carrying = true;
					carriedObject = p.gameObject;
					p.gameObject.GetComponent<Rigidbody>().useGravity = false;
					p.gameObject.GetComponent<Collider>().enabled = false;
				}
			}
		}
	}

	void collectKey()
    {
		int x = Screen.width / 2;
		int y = Screen.height / 2;

		Ray ray = mainCamera.GetComponent<Camera>().ScreenPointToRay(new Vector3(x, y));
		RaycastHit hit;
		if (Physics.Raycast(ray, out hit))
		{
			Key p = hit.collider.GetComponent<Key>();
			if (p != null)
			{
				if (Input.GetKeyDown(KeyCode.F))
				{
					Debug.Log("Key collected");
					Destroy(hit.collider.gameObject);
					Game.keysCollected += 1;
				}
			}
		}
	}

	void checkDrop()
	{
		if (Input.GetKeyDown(KeyCode.E))
		{
			dropObject();
		}
	}

	void dropObject()
	{
		carrying = false;
		carriedObject.gameObject.GetComponent<Rigidbody>().useGravity = true;
		carriedObject.gameObject.GetComponent<Collider>().enabled = true;
		carriedObject = null;
		distance = 1f;
	}

	void rotate()
	{
		if (Input.GetKey(KeyCode.LeftArrow))
		{
			carriedObject.transform.Rotate(0.0f, 100 * Time.deltaTime, 0.0f);
		}
		if (Input.GetKey(KeyCode.RightArrow))
		{
			carriedObject.transform.Rotate(0.0f, -100 * Time.deltaTime, 0.0f);
		}
		if (Input.GetKey(KeyCode.DownArrow))
		{
			carriedObject.transform.Rotate(-100 * Time.deltaTime, 0.0f, 0.0f);
		}
		if (Input.GetKey(KeyCode.UpArrow))
		{
			carriedObject.transform.Rotate(100 * Time.deltaTime, 0.0f, 0.0f);
		}

		if (Input.GetKey(KeyCode.LeftArrow) && Input.GetKey(KeyCode.DownArrow))
		{
			carriedObject.transform.Rotate(-50 * Time.deltaTime, 50 * Time.deltaTime, 0.0f);
		}
		if (Input.GetKey(KeyCode.RightArrow) && Input.GetKey(KeyCode.DownArrow))
		{
			carriedObject.transform.Rotate(-50 * Time.deltaTime, -50 * Time.deltaTime, 0.0f);
		}
		if (Input.GetKey(KeyCode.LeftArrow) && Input.GetKey(KeyCode.UpArrow))
		{
			carriedObject.transform.Rotate(50 * Time.deltaTime, 50 * Time.deltaTime, 0.0f);
		}
		if (Input.GetKey(KeyCode.RightArrow) && Input.GetKey(KeyCode.UpArrow))
		{
			carriedObject.transform.Rotate(50 * Time.deltaTime, -50 * Time.deltaTime, 0.0f);
		}
	}

	void zoom()
    {
        if (distance > 0.5 && Input.GetKey(KeyCode.Alpha1)) {
            distance -= 0.01f;
		}
		if (distance < 1 && Input.GetKey(KeyCode.Alpha2))
		{
			distance += 0.01f;
		}
	}
}
