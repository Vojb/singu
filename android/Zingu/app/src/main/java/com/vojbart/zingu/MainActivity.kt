package com.vojbart.zingu

import android.annotation.SuppressLint
import android.annotation.TargetApi
import android.graphics.Color
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*
import android.content.DialogInterface
import android.bluetooth.BluetoothAdapter
import android.content.Context
import android.support.v7.app.AlertDialog
import android.content.Intent
import android.os.Handler
import android.util.Log
import android.view.MotionEvent
import android.view.View
import android.view.Window
import android.view.WindowManager
import android.widget.Toast
import io.reactivex.Completable
import io.reactivex.schedulers.Schedulers
import android.os.VibrationEffect
import android.os.Build
import android.os.Vibrator



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
        text_connect_to_zingu.text = "DISCONNECT"
        text_connect_to_zingu.setOnClickListener {
            bluetoothCom.disconnect()
        }
        enableButtons(true)
    }


    override fun onDisconnected() {
        background_layout.background = getDrawable(R.color.red)
        progressBar.visibility = View.GONE
        text_connect_to_zingu.text = "CONNECT"
        text_connect_to_zingu.setOnClickListener {
            bluetoothCom.connect("98:D3:32:70:61:BB")

        }
        enableButtons(false)

    }

    override fun onConnecting() {
        progressBar.visibility = View.VISIBLE
    }

    override fun onDisconnecting() {
        progressBar.visibility = View.VISIBLE

    }

    var REQUEST_BLUETOOTH = 1

    lateinit var bluetoothCom: BluetoothCom

    private var mHandler: Handler? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        window.setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN)
        requestWindowFeature(Window.FEATURE_NO_TITLE)
        setContentView(R.layout.activity_main)
        window.navigationBarColor= Color.BLACK
        enableButtons(false)

        val BTAdapter = BluetoothAdapter.getDefaultAdapter()
        bluetoothCom = BluetoothCom(this)
        bluetoothCom.iCom = this
        if (!BTAdapter.isEnabled) {
            val enableBT = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
            startActivityForResult(enableBT, REQUEST_BLUETOOTH)
        }

        text_connect_to_zingu.setOnClickListener {
            bluetoothCom.connect("98:D3:32:70:61:BB")
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


        button_drive.setOnTouchListener { _, event ->
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
                    go("b")
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

    }

    override fun onResume() {
        super.onResume()
        fullScreen()
        window.setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN)

    }

    private fun enableButtons(bool:Boolean) {
        button_drive.isEnabled = bool
        button_reverse.isEnabled = bool
        button_right.isEnabled = bool
        button_left.isEnabled = bool
    }

    @TargetApi(Build.VERSION_CODES.O)
    fun Runnable.go(string: String) {
        if (mHandler != null) {
            bluetoothCom.write(string)
            Log.d("pressed", string)
            mHandler!!.postDelayed(this, 0)
            val v = getSystemService(Context.VIBRATOR_SERVICE) as Vibrator

                v.vibrate(VibrationEffect.createOneShot(100, VibrationEffect.DEFAULT_AMPLITUDE))

        }
    }

    private fun buttonPressed(event: MotionEvent, mAction: Runnable) {
        when (event.action) {
            MotionEvent.ACTION_DOWN -> {
                mHandler = Handler()
                mHandler!!.postDelayed(mAction, 20)
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

    @SuppressLint("ObsoleteSdkInt")
    fun fullScreen() {
        if (Build.VERSION.SDK_INT in 12..18) { // lower api
            val v = this.window.decorView
            v.systemUiVisibility = View.GONE
        } else if (Build.VERSION.SDK_INT >= 19) {
            //for new api versions.
            val decorView = window.decorView
            val uiOptions = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION or View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
            decorView.systemUiVisibility = uiOptions
        }
    }
}
