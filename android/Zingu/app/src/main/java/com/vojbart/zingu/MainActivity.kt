package com.vojbart.zingu

import android.graphics.Color
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*
import android.content.DialogInterface
import android.bluetooth.BluetoothAdapter
import android.support.v7.app.AlertDialog
import android.content.Intent
import android.os.Handler
import android.util.Log
import android.view.MotionEvent
import android.view.View
import android.widget.Toast
import io.reactivex.Completable
import io.reactivex.schedulers.Schedulers

interface CommunicationInterface {
    fun onConnectedToDevice()
    fun onDisconnected()
    fun onConnecting()
    fun onDisconnecting()
}


class MainActivity : AppCompatActivity(), CommunicationInterface {
    override fun onConnectedToDevice() {
        background_layout.background = getDrawable(R.color.colorPrimary)
        progressBar.visibility = View.GONE
    }

    override fun onDisconnected() {
        background_layout.background = getDrawable(R.color.red)
        progressBar.visibility = View.GONE

    }

    override fun onConnecting() {
        progressBar.visibility = View.VISIBLE
    }

    override fun onDisconnecting() {
        progressBar.visibility = View.VISIBLE

    }

    var buttonPressed = false

    var REQUEST_BLUETOOTH = 1

    lateinit var bluetoothCom: BluetoothCom

    private var mHandler: Handler? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        window.navigationBarColor = Color.TRANSPARENT

        val BTAdapter = BluetoothAdapter.getDefaultAdapter()
        bluetoothCom = BluetoothCom(this)
        bluetoothCom.iCom = this
        if (!BTAdapter.isEnabled) {
            val enableBT = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
            startActivityForResult(enableBT, REQUEST_BLUETOOTH)
        }

        // Phone does not support Bluetooth so let the user know and exit.
        if (BTAdapter == null) {
            AlertDialog.Builder(this)
                    .setTitle("Not compatible")
                    .setMessage("Your phone does not support Bluetooth")
                    .setPositiveButton("Exit") { _, _ -> System.exit(0) }
                    .setIcon(android.R.drawable.ic_dialog_alert)
                    .show()
        }


        button_drive.setOnTouchListener { v, event ->
            buttonPressed(event, object : Runnable {
                override fun run() {
                    go("f")
                }
            })
            false
        }

        button_reverse.setOnTouchListener { v, event ->
            buttonPressed(event, object : Runnable {
                override fun run() {
                    go("r")
                }
            })
            false
        }
        button_left.setOnTouchListener { v, event ->
            buttonPressed(event, object : Runnable {
                override fun run() {
                    go("l")
                }
            })
            false
        }
        button_right.setOnTouchListener { v, event ->
            buttonPressed(event, object : Runnable {
                override fun run() {
                    go("r")
                }
            })
            false
        }

        image_bluetooth.setOnClickListener {
            bluetoothCom.showDeviceListDialog()
        }

        text_connect_to_zingu.setOnClickListener {
            bluetoothCom.connect("98:D3:32:70:61:BB")

        }
    }

    fun Runnable.go(string: String) {
        if (mHandler != null) {
            bluetoothCom.write(string)
            Log.d("pressed", string)
            mHandler!!.postDelayed(this, 50)
        }
    }

    private fun buttonPressed(event: MotionEvent, mAction: Runnable) {
        when (event.action) {
            MotionEvent.ACTION_DOWN -> {
                mHandler = Handler()
                mHandler!!.postDelayed(mAction, 50)
                true
            }
            // Do something
            MotionEvent.ACTION_UP -> {
                if (mHandler == null)
                    mHandler!!.removeCallbacks(mAction)
                mHandler = null
                true

            }
            // No longer down
        }
    }
}
