from flask import Flask, render_template, jsonify
import subprocess

app = Flask(__name__)

@app.route("/")
def home():
    return render_template("index.html")


@app.route("/run", methods=["POST"])
def run_process():
    try:
        result = subprocess.run(
            ["./process_system"],
            capture_output=True,
            text=True,
            timeout=15
        )

        return jsonify({
            "success": result.returncode == 0,
            "output": result.stdout,
            "error": result.stderr
        })

    except subprocess.TimeoutExpired:
        return jsonify({
            "success": False,
            "output": "",
            "error": "Process execution timed out."
        }), 500

    except Exception as e:
        return jsonify({
            "success": False,
            "output": "",
            "error": str(e)
        }), 500


if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=False)
